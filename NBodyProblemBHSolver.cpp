#include "GausNewtonSolver.hpp"
#include "Options/Constants.h"
#include "Structures/ModelValue.hpp"
#include "Structures/SimulationVector.hpp"
#include "window_sph_graph.hpp"

#include <QApplication>
#include <QDebug>
#include <QLineSeries>
#include <QPointF>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class Simulation {
private:
    // вектор указателей на объекты класса Star
    vector<Star*> stars;

    vector<vector<double>> init_states;

    vector<vector<ModelValue>> values;

    // окно для графика в сферических координатах
    Window_Sph_Graph* window_sph;

    // шаг для метода численного интегрирования
    double dt;

    // временные значения для метода численного интегрирования
    SimulationVector k1, k2, k3, k4;

    size_t star_index;

public:
    Simulation(Star* S2, Star* S38, Star* S55, double dt)
        : dt(dt)
    {
        stars = { S2, S38, S55 };
        for (auto star : stars)
            init_states.push_back(star->getInit_state());

        window_sph = new Window_Sph_Graph(nullptr);
    }

    void calculateDF_dB(const vector<double>& X, const double& r_pos, Matrix& dF_dB)
    {
        // da/dM = - G r / |r| ^ 3
        for (int i = 0; i < SIZE_VECTOR; i++) {
            double debug_var = -(X[i] * G) / pow(r_pos, 3);
            dF_dB.setElement(3 + i, 6, debug_var);
        }
    }

    Matrix calculateDF_dX(const vector<double>& X, const double& r_pos, Matrix& dF_dX)
    {
        double M = stars[star_index]->getInit_state()[6];
        for (int i = 3; i < dF_dX.Get_sizeN(); i++) {
            for (int j = 0; j < SIZE_VECTOR; j++) {
                if (i == j + 3) {
                    dF_dX.setElement(i, j, calculateDA_dRn(X[j], r_pos, M));
                }
            }
        }

        double dAxy_dyx = (3 * G * M * X[0] * X[1]) / (pow(r_pos, 5));
        double dAxz_dzx = (3 * G * M * X[0] * X[2]) / (pow(r_pos, 5));
        double dAyz_dzy = (3 * G * M * X[1] * X[2]) / (pow(r_pos, 5));

        dF_dX.setElement(3, 1, dAxy_dyx);
        dF_dX.setElement(4, 0, dAxy_dyx);

        dF_dX.setElement(3, 2, dAxz_dzx);
        dF_dX.setElement(5, 0, dAxz_dzx);

        dF_dX.setElement(4, 2, dAyz_dzy);
        dF_dX.setElement(5, 1, dAyz_dzy);

        for (int i = 0; i < SIZE_VECTOR; i++) {
            for (int j = 3; j < dF_dX.Get_sizeM(); j++) {
                if ((j - 3) == i)
                    dF_dX.setElement(i, j, 1);
            }
        }
        return dF_dX;
    }

    double calculateDA_dRn(const double& x, const double& r_pos, const double& M)
    {
        // calculate da_dr (x, y, z)
        double denominator = pow(r_pos, 6);
        double numerator = -G * M * (pow(r_pos, 3) - 3 * x * x * r_pos);

        return numerator / denominator;
    }

    /**
     * @brief equationPN - Функция правой части
     * @param state - вектор состояния
     * @param answer - следующий вектор состояния
     */
    void equationPN(const SimulationVector& state, SimulationVector& answer)
    {
        double r_pos = 0, r_speed = 0, prod_vectors = 0;
        double M = init_states[star_index][6];
        answer.clearX_vector();
        vector<double> accel(SIZE_VECTOR);

        for (int i = 0; i < SIZE_VECTOR; ++i) {
            answer.setElementX_vector(i, dt * state.getX_vector()[i + SIZE_VECTOR]); // dr = v * dt
        }

        for (int i = 0; i < SIZE_VECTOR; i++) {
            r_pos += pow(state.getX_vector()[i], 2);
            r_speed += pow(state.getX_vector()[i + SIZE_VECTOR], 2);
            prod_vectors += state.getX_vector()[i] * state.getX_vector()[SIZE_VECTOR + i];
        }
        r_pos = sqrt(r_pos);
        r_speed = sqrt(r_speed);

        double Newton_factor = -(G * M) / (pow(c, 2) * pow(r_pos, 3));
        double prod = pow(c, 2) - 4 * (G * M) / r_pos + pow(r_speed, 2);

        for (int i = 0; i < SIZE_VECTOR; i++) {
            accel[i] = Newton_factor * (prod * state.getX_vector()[i] - 4 * state.getX_vector()[i + 3] * prod_vectors);
        }

        for (int i = SIZE_VECTOR; i < SIZE_VECTOR * 2; ++i) {
            answer.setElementX_vector(i, dt * accel[i - 3]); // dv = a * dt
        }

        Matrix DF__dr0_dv0_dM = Matrix(6, 7);

        Matrix dF__dr0_dv0_dM = Matrix(6, 7);

        Matrix dF__dr_dv = Matrix(6, 6);

        calculateDF_dB(state.getX_vector(), r_pos, dF__dr0_dv0_dM);

        calculateDF_dX(state.getX_vector(), r_pos, dF__dr_dv);

        // dF_dB = dF_dB_prev + dF_dX * dX_dB
        DF__dr0_dv0_dM = dF__dr0_dv0_dM + dF__dr_dv * state.getDX__dr0_dv0_dM();

        // new DX__dr0_dv0_dM = dt * dF_dB
        answer.setDX__dr0_dv0_dM(dt * DF__dr0_dv0_dM);

        //        Matrix dF_dB = Matrix(6, 7);
        //        calculateDF_dB(state.getX_vector(), r_pos, dF_dB);

        //        answer.setDF_dX(calculateDF_dX(state.getX_vector(), r_pos));

        //        // dX_dB = dF_dB + dF_dX * dX_dB
        //        auto temp_matrix = answer.getDF_dX() * state.getDX_dB();
        //        answer.setDX_dB(dF_dB + temp_matrix);
    }

    /**
     * @brief translate_to_spherical - функция перевода декартовых координат в сферические
     * @param current_state - текущий вектор состояния с декартовыми координатами
     * @return pair, где первый элемент - Decl., а второй - R.A.
     */
    pair<double, double> translate_to_spherical(const vector<double>& current_state)
    {
        pair<double, double> res;
        vector<double> pos = { current_state[0] * 1000, current_state[1] * 1000,
            current_state[2] * 1000 };
        //        double r_pos = 0, r_pos2d = 0;

        pos[0] += X_BH;
        pos[1] += Y_BH;
        pos[2] += Z_BH;

        //        for (size_t i = 0; i < SIZE_VECTOR; i++)
        //            r_pos += pow(pos[i], 2);

        //        for (size_t i = 0; i < 2; i++)
        //            r_pos2d += pow(pos[i], 2);

        //        r_pos = sqrt(r_pos);
        //        r_pos2d = sqrt(r_pos2d);

        double RA = atan2(pos[1], pos[0]);
        double Decl = atan2(pos[2], sqrt(pow(pos[0], 2) + pow(pos[1], 2)));
        // double Decl = asin(pos[2] / r_pos);
        //        double RA = asin(pos[1] / r_pos2d);

        Decl -= 1.05249165;
        RA -= 1.70605945;

        Decl *= Rad_to_Arc_sec;
        RA *= Rad_to_Arc_sec;

        res = make_pair(Decl, RA);

        return res;
    }

    /**
     * @brief RK4 - Классический метод Рунге-Кутты
     * @param state - вектор аргументов с предыдущего шага
     * @return - вектор значений в следующей точке
     */
    void RK4(const SimulationVector& state, SimulationVector& res)
    {

        equationPN(state, k1);
        equationPN(state + (0.5 * k1), k2);
        equationPN(state + (0.5 * k2), k3);
        equationPN(state + k3, k4);

        res = (state + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0);
    }

    bool isAllCalculated(vector<priority_queue<int, vector<int>, greater<int>>>& place_numbers)
    {
        int count = 0;
        for (const auto& pq : place_numbers) {
            if (pq.empty())
                count++;
        }
        if (count == int(stars.size()))
            return true;
        return false;
    }

    /**
     * @brief runSimulation - Функция для запуска расчета
     * @param time - время рассчета
     */
    void runSimulation(double time)
    {
        cout << "Simulation is running...\n";
        int steps = int(time / dt);
        int counter = 0;

        vector<SimulationVector> stars_result(stars.size());
        vector<priority_queue<int, vector<int>, greater<int>>> place_numbers;

        values.resize(stars.size());
        place_numbers.resize(stars.size());
        for (size_t i = 0; i < place_numbers.size(); i++)
            place_numbers[i] = stars[i]->findIndexModelValue();

        while (steps > 0) {
            for (star_index = 0; star_index < stars.size(); star_index++) {
                auto& cur_state = stars_result[star_index];
                auto RA_Decl = translate_to_spherical(cur_state.getX_vector());

                RK4(stars[star_index]->getPrev_state(), cur_state);

                stars[star_index]->add_state_to_history(cur_state);
                stars[star_index]->add_state_to_sph_history(RA_Decl);
                stars[star_index]->setPrev_state(cur_state);

                if (place_numbers[star_index].top() == counter) {
                    place_numbers[star_index].pop();
                    addNewModelValue(values[star_index], cur_state, RA_Decl);
                }
            }
            if (isAllCalculated(place_numbers))
                break;
            steps--;
            counter++;
        }
    }

    void transformDR_DB(Matrix& new_DR_dB, ModelValue& value)
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < Size_Matrix_B; j++) {
                new_DR_dB.setElement(i, j, value.getDX_dB().Get_Matrix()[i][j]);
            }
        }
    }

    void inverseTask(Star* cur_star, vector<ModelValue>& value_vector)
    {
        GausNewtonSolver GNSolver;
        int num_rows = int(cur_star->getSpherical_history_obs().size());
        Matrix R = Matrix(num_rows * 2, 1);
        Matrix A = Matrix(num_rows * 2, 7);

        double d_RA = 0, d_Decl = 0;

        for (int i = 0; i < num_rows; i++) {
            GNSolver.calculate_dRA_Decl_dR(value_vector[i]);
            Matrix dR_dB = Matrix(2, 7);
            Matrix dX_dB = Matrix(3, 7);

            int temp = int(round(cur_star->getSpherical_history_obs()[i].first * 365));
            int position = (cur_star->GetIndex() + temp) % cur_star->getSpherical_history_model().size();

            transformDR_DB(dX_dB, value_vector[i]);
            dR_dB = (-1 * (*value_vector[i].getDRA_Decl_dR()) * dX_dB);

            // delta = table value - model value
            d_RA = cur_star->getSpherical_history_obs()[i].second.first - cur_star->getSpherical_history_model()[position].first;
            d_Decl = cur_star->getSpherical_history_obs()[i].second.second - cur_star->getSpherical_history_model()[position].second;

            while ((d_RA > PI) or (d_RA < -PI)) {
                int sign = d_RA > PI ? -1 : 1;
                d_RA = d_RA + sign * 2 * PI;
            }

            for (int j = 0; j < 7; j++) {
                A.setElement(2 * i, j, dR_dB.Get_matrix()[0][j]);
                A.setElement(2 * i + 1, j, dR_dB.Get_matrix()[1][j]);
            }

            R.setElement(2 * i, 0, d_RA);
            R.setElement(2 * i + 1, 0, d_Decl);
        }
        cur_star->setInit_state(GNSolver.Gauss_Newton(cur_star->getInit_state(), A, R));
    }

    void addNewModelValue(vector<ModelValue>& MV_vector, const SimulationVector& state, const pair<double, double>& RA_Decl)
    {
        ModelValue new_value;
        new_value.setDX_dB(state.getDX__dr0_dv0_dM());
        new_value.setCortesian_pos(state.getX_vector());
        new_value.setSpeed(state.getX_vector());
        new_value.setRA(RA_Decl.second);
        new_value.setDecl(RA_Decl.first);
        MV_vector.push_back(new_value);
    }

    void generalSolution()
    {
        int i = 0;
        while (i < Iters_Num) {
            cout << "Итерация " << i + 1 << " :\n";
            runSimulation(HOUR * DAY * YEAR * 20);
            // inverse_problem
            for (size_t star_index = 0; star_index < 3; star_index++) {
                inverseTask(stars[star_index], values[star_index]);
            }

            i++;
            //            clearData();
        }
    }

    void clearData()
    {
        values.clear();
        for (star_index = 0; star_index < stars.size(); star_index++) {
            stars[star_index]->clearHistory();
            stars[star_index]->setInit_state(init_states[star_index]);
        }
    }

    //    void printInits()
    //    {
    //        for (star_index = 0; star_index < stars.size(); star_index++) {
    //            cout << "Star " << star_index + 1 << "\n";
    //            for (auto state : init_states[star_index]) {
    //                for (double& b : state)
    //                    cout << b << " ";
    //                cout << "\n\n";
    //            }
    //        }
    //    }

    /**
     * @brief printRes - Функция для формирования вывода графика в окне MainWindow
     */
    void printRes()
    {
        double min_data_x = 100.0, min_data_y = 100.0;
        double max_data_x = -100.0, max_data_y = -100.0;
        QtCharts::QLineSeries* first = new QtCharts::QLineSeries();
        QtCharts::QLineSeries* second = new QtCharts::QLineSeries();
        QtCharts::QLineSeries* third = new QtCharts::QLineSeries();
        vector<QtCharts::QLineSeries*> data_sph = { first, second, third };

        for (size_t index = 0; index < stars.size(); index++) {

            for (auto state_sph : stars[index]->getSpherical_history_model()) {
                min_data_x = (min_data_x > state_sph.first) ? state_sph.first : min_data_x;
                min_data_y = (min_data_y > state_sph.second) ? state_sph.second : min_data_y;

                max_data_x = (max_data_x < state_sph.first) ? state_sph.first : max_data_x;
                max_data_y = (max_data_y < state_sph.second) ? state_sph.second : max_data_y;
                *data_sph[index] << QPointF(state_sph.first, state_sph.second);
            }
        }
        window_sph->printGraph(first, second, third, min_data_x, min_data_y, max_data_x, max_data_y);
    }
};

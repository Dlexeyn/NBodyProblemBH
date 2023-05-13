#include "window_sph_graph.hpp"
#include "Options/Constants.h"
#include "Structures/Star.cpp"
#include "Structures/SimulationVector.hpp"

#include <QApplication>
#include <cmath>
#include <QLineSeries>
#include <QPointF>
#include <vector>
#include <fstream>

using namespace std;

class Simulation
{
private:
    // вектор указателей на объекты класса Star
    vector<Star*> stars;

    // окно для графика в сферических координатах
    Window_Sph_Graph *window_sph;

    // шаг для метода численного интегрирования
    double dt;

    // временные значения для метода численного интегрирования
    SimulationVector k1, k2, k3, k4;

public:
    Simulation(Star *S2, Star *S38, Star *S55, double dt)
        : dt(dt)
    {
        stars = { S2, S38, S55 };
        window_sph = new Window_Sph_Graph(nullptr);
    }


    void calculateDF_dB(const vector<double> &X, const double &r_pos, Matrix &dF_dB)
    {
        //da/dM = - G r / |r| ^ 3
        for(int i = 0; i < SIZE_VECTOR; i++)
            dF_dB.setElement(3 + i, 6, -(X[i] * G) / pow(r_pos, 3));
    }

    Matrix calculateDF_dX(const vector<double> &X, const double &r_pos)
    {
        Matrix dF_dX = Matrix(6, 6);
        for(int i = 3; i < dF_dX.Get_sizeN(); i++)
        {
            for(int j = 0; j < SIZE_VECTOR; j++)
                dF_dX.setElement(i, j, calculateDA_dRn(X[j], r_pos));
        }

        for(int i = 0; i < SIZE_VECTOR; i++)
        {
            for(int j = 3; j < dF_dX.Get_sizeM(); j++)
            {
                if((j - 3) == i)
                    dF_dX.setElement(i, j, 1);
            }
        }
        return dF_dX;
    }

    double calculateDA_dRn(const double &x, const double &r_pos)
    {
        // calculate da_dr (x, y, z)
        double denominator = pow(r_pos, 6);
        double numerator = - G * M * (pow(r_pos, 3) - 3 * x * x * r_pos);
        return numerator / denominator;
    }


    /**
     * @brief equationPN - Функция правой части
     * @param state - вектор состояния
     * @param answer - следующий вектор состояния
     */
    void equationPN(const SimulationVector &state, SimulationVector &answer)
    {
        double r_pos = 0, r_speed = 0, prod_vectors = 0;
        answer.clearX_vector();
        vector<double> accel(SIZE_VECTOR);

        for (int i = 0; i < SIZE_VECTOR; ++i) {
            answer.setElementX_vector(i, dt * state.getX_vector()[i + SIZE_VECTOR]); // dr = v * dt
        }

        for(int i = 0; i < SIZE_VECTOR; i++)
        {
            r_pos += pow(state.getX_vector()[i], 2);
            r_speed += pow(state.getX_vector()[i + SIZE_VECTOR], 2);
            prod_vectors += state.getX_vector()[i] * state.getX_vector()[SIZE_VECTOR + i];
        }
        r_pos = sqrt(r_pos);
        r_speed = sqrt(r_speed);

        double Newton_factor = - (G * M) / ( pow(c, 2) * pow(r_pos, 3) );
        double prod = pow(c, 2) - 4 * (G * M)  / r_pos + pow(r_speed, 2);

        for(int i = 0; i < SIZE_VECTOR; i++)
        {
            accel[i] = Newton_factor * (prod * state.getX_vector()[i]
                                        - 4 * state.getX_vector()[i + 3] * prod_vectors);
        }

        for (int i = SIZE_VECTOR; i < SIZE_VECTOR * 2; ++i) {
            answer.setElementX_vector(i, dt * accel[i - 3]);    // dv = a * dt
        }

        Matrix dF_dB = Matrix(6, 7);
        calculateDF_dB(state.getX_vector(), r_pos, dF_dB);

        answer.setDF_dX(calculateDF_dX(state.getX_vector(), r_pos));

        // dX_dB = dF_dB + dF_dX * dX_dB
        answer.setDX_dB(dF_dB + answer.getDF_dX() * state.getDX_dB());
    }

    /**
     * @brief translate_to_spherical - функция перевода декартовых координат в сферические
     * @param current_state - текущий вектор состояния с декартовыми координатами
     * @return pair, где первый элемент - Decl., а второй - R.A.
     */
    pair<double,double> translate_to_spherical(const vector<double> &current_state)
    {
        pair<double, double> res;
        vector<double> pos = {current_state[0] * 1000, current_state[1] * 1000,
                              current_state[2] * 1000};
        double r_pos = 0, r_pos2d = 0;

        pos[0] += X_BH;
        pos[1] += Y_BH;
        pos[2] += Z_BH;

        for(size_t i = 0; i < SIZE_VECTOR; i++)
            r_pos += pow(pos[i], 2);

        for(size_t i = 0; i < 2; i++)
            r_pos2d += pow(pos[i], 2);

        r_pos = sqrt(r_pos);
        r_pos2d = sqrt(r_pos2d);

        double Decl = asin(pos[2] / r_pos);
        double RA = asin(pos[1] / r_pos2d);

        Decl -= 1.05249165;
        RA -= 1.4355335;

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
    void RK4(const SimulationVector &state, SimulationVector &res)
    {

        equationPN(state, k1);
        equationPN(state + (0.5 * k1), k2);
        equationPN(state + (0.5 * k2), k3);
        equationPN(state + k3, k4);

        res = state + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }

    /**
     * @brief runSimulation - Функция для запуска расчета
     * @param time - время рассчета
     */
    void runSimulation(double time)
    {
        cout << "Simulation is running...\n";
        int steps = int(time / dt);

        vector<SimulationVector> stars_result(stars.size());

        while(steps > 0)
        {
            for(size_t index = 0; index < stars.size(); index++)
            {
                RK4(stars[index]->getPrev_state(), stars_result[index]);

                stars[index]->add_state_to_history(stars_result[index]);
                stars[index]->add_state_to_sph_history(translate_to_spherical(stars_result[index].getX_vector()));
                stars[index]->setPrev_state(stars_result[index]);
            }
            steps--;
        }
    }

    /**
     * @brief printRes - Функция вывода графика в окне MainWindow
     */
    void printRes()
    {
        double min_data_x = 100.0, min_data_y = 100.0;
        double max_data_x = -100.0, max_data_y = -100.0;
        QtCharts::QLineSeries *first = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *second = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *third = new QtCharts::QLineSeries();
        vector<QtCharts::QLineSeries*> data_sph = { first, second, third };

        for(size_t index = 0; index < stars.size(); index++)
        {

            for(auto state_sph : stars[index]->getSpherical_history())
            {
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





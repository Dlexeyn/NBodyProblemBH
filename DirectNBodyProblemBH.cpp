#include "window_sph_graph.hpp"
#include "Constants.h"
#include "Star.cpp"

#include <QApplication>
#include <bits/stdc++.h>
#include <QLineSeries>
#include <QPointF>
#include <fstream>

using namespace std;


double operator * (const vector<double> &v1, const vector<double> &v2){
    double res = 0;
    for (size_t i = 0; i < v1.size(); i++){
        res += v1[i] * v2[i];
    }
    return res;
}

vector<double> operator * (const double d, const vector<double> &v1){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] * d;
    }
    return res;
}

vector<double> operator * (const vector<double> &v1, const double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] * d;
    }
    return res;
}

vector<double> operator / (const vector<double> &v1, const double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] / d;
    }
    return res;
}

vector<double> operator - (const vector<double> &v1, const vector<double> &v2){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vector<double> operator + (const vector<double> &v1, const vector<double> &v2){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] + v2[i];
    }
    return res;
}





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
    vector<double> k1, k2, k3, k4;

public:
    Simulation(Star *S2, Star *S38, Star *S55, double dt)
        : dt(dt)
    {
        stars = { S2, S38, S55 };
        window_sph = new Window_Sph_Graph(nullptr);
    }

    /**
     * @brief equationPN - Функция правой части
     * @param state - вектор состояния
     * @param answer - следующий вектор состояния
     */
    void equationPN(const vector<double> &state, vector<double> &answer)
    {
        double r_pos = 0, r_speed = 0, prod_vectors = 0;
        answer.clear();
        answer.resize(SIZE_VECTOR * 2);
        vector<double> accel(SIZE_VECTOR);

        for (int i = 0; i < SIZE_VECTOR; ++i) {
            answer[i] = dt * state[i + SIZE_VECTOR];      // dr = v * dt
        }

        for(int i = 0; i < SIZE_VECTOR; i++)
        {
            r_pos += pow(state[i], 2);
            r_speed += pow(state[i + SIZE_VECTOR], 2);
            prod_vectors += state[i] * state[SIZE_VECTOR + i];
        }
        r_pos = sqrt(r_pos);
        r_speed = sqrt(r_speed);

        double Newton_factor = - (G * M) / ( pow(c, 2) * pow(r_pos, 3) );
        double prod = pow(c, 2) - 4 * (G * M)  / r_pos + pow(r_speed, 2);

        for(int i = 0; i < SIZE_VECTOR; i++)
        {
            accel[i] = Newton_factor * (prod * state[i] - 4 * state[i + 3] * prod_vectors);
        }

        for (int i = SIZE_VECTOR; i < SIZE_VECTOR * 2; ++i) {
            answer[i] = dt * accel[i - 3];      // dv = a * dt
        }

    }

    /**
     * @brief translate_to_spherical - функция перевода декартовых координат в сферические
     * @param current_state - текущий вектор состояния с декартовыми координатами
     * @return pair, где первый элемент - Decl., а второй - R.A.
     */
    pair<double,double> translate_to_spherical(const vector<double> &current_state)
    {
        pair<double, double> res;
        vector<double> pos = {current_state[0] * 1000, current_state[1] * 1000, current_state[2] * 1000};
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

    //
    /**
     * @brief RK4 - Классический метод Рунге-Кутты
     * @param state - вектор аргументов с предыдущего шага
     * @return - вектор значений в следующей точке
     */
    void RK4(const vector<double> &state, vector<double> &res)
    {
        equationPN(state, k1);
        equationPN(state + (k1 * 0.5), k2);
        equationPN(state + (k2 * 0.5), k3);
        equationPN(state + k3, k4);

        res = state + (k1 + k2 * 2 + k3 * 2 + k4) / 6;
    }

    /**
     * @brief runSimulation - Функция для запуска расчета
     * @param time - время рассчета
     */
    void runSimulation(double time)
    {
        cout << "Simulation is running...\n";
        int steps = int(time / dt);

        vector<vector<double>> stars_result(stars.size());

        while(steps > 0)
        {
            for(size_t index = 0; index < stars.size(); index++)
            {
                RK4(stars[index]->getPrev_state(), stars_result[index]);
                stars[index]->add_state_to_history(stars_result[index]);
                stars[index]->add_state_to_sph_history(translate_to_spherical(stars_result[index]));
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





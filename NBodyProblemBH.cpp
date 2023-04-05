#include "mainwindow.hpp"

#include <Q3DScatter>
#include <QtDataVisualization>
#include <QApplication>
#include <bits/stdc++.h>
#include <fstream>

using namespace QtDataVisualization;
using namespace std;

// constants
double G = 6.674e-20; // gravitational constant in km^3/kg/s^2
double c = 300000.0;               //speed of light in km/s
double M = 7.9556e+36;  // mass of the black hole in kg

int HOUR = 3600;
int DAY = 24;
int YEAR = 365;


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
    // начальное состояние
    vector<double> state;

    // окно для графика
    MainWindow *window;

    // история состояний
    vector<vector<double>> history;

    // шаг для метода численного интегрирования
    double dt;

    // значения для метода численного интегрирования
    vector<double> k1, k2, k3, k4;

public:
    Simulation(vector<double> state0, double dt)
        : state(state0), dt(dt)
    {
        window = new MainWindow(nullptr);
    }

    // Функция правой части
    void equationPN(const vector<double> &state, vector<double> &answer)
    {
        answer.clear();
        answer.resize(6);
        vector<double> pos, speed, accel(3);

        pos = {state[0], state[1], state[2]};
        speed = {state[3], state[4], state[5]};

        for (int i = 0; i < 3; ++i) {
            answer[i] = dt * speed[i];      // dr = v * dt
        }

        double rpos = sqrt(pow(state[0], 2) + pow(state[1], 2) + pow(state[2], 2));
        double rspeed = sqrt(pow(state[3], 2) + pow(state[4], 2) + pow(state[5], 2));
        double prod_vectors = state[0] * state[3] + state[1] * state[4] + state[2] * state[5];

        double NewtonScal = - (G * M) / ( pow(c, 2) * pow(rpos, 3) );
        double prod = pow(c, 2) - 4 * (G * M)  / rpos + pow(rspeed, 2);

        for(int i = 0; i < 3; i++)
        {
            accel[i] = NewtonScal * (prod * state[i] - 4 * state[i + 3] * prod_vectors );
        }

        for (int i = 3; i < 6; ++i) {
            answer[i] = dt * accel[i - 3];      // dv = a * dt
        }

    }

    // Классический метод Рунге-Кутты
    vector<double> RK4(const vector<double> &state)
    {
        vector<double> res;
        equationPN(state, k1);
        equationPN(state + (k1 * 0.5), k2);
        equationPN(state + (k2 * 0.5), k3);
        equationPN(state + k3, k4);

        res = state + (k1 + k2 * 2 + k3 * 2 + k4) / 6;

        return res;
    }

    // Функция для запуска расчета
    void runSimulation(double time)
    {
        int steps = int(time / dt);
        vector<double> res = state;

        while(steps > 0)
        {
            res = RK4(res);
            history.push_back(res);
            steps--;
        }
    }

    // Функция вывода на график в окне MainWindow
    void printRes()
    {
        QScatterDataArray data;
        ofstream out;
        out.open("res.txt", ios::out);

        for(auto &state : history)
        {
            data << QVector3D(state[0], state[1], state[2]);
            out << state[0] << " " << state[1] << " " << state[2] << " "
                << state[3] << " " << state[4] << " " << state[5] << endl;
        }
        window->printGraph(data);
        out.close();
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    double dt = HOUR;
    vector<double> state0 = {-1.98477e+11,
                             3.44699e+10,
                             -1.02789e+11,
                             -70.418,
                             710.873,
                             317.454};    //vz0

    Simulation sim(state0, dt);
    sim.runSimulation(HOUR * DAY * YEAR * 15);
    sim.printRes();

    return a.exec();
}

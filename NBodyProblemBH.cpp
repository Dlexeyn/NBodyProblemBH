#include "mainwindow.hpp"

#include <Q3DScatter>
#include <QtDataVisualization>
#include <QApplication>
#include <bits/stdc++.h>

using namespace QtDataVisualization;
using namespace std;

// constants
double G = 6.674 * pow(10, -11);  // gravitational constant in m^3/kg/s^2
double c = 299792458;               //speed of light in m/s
double M = 8.26 * pow(10, 36);  // mass of the black hole in kg

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
    vector<double> state;   // начальное состояние
    MainWindow *window;
    vector<vector<double>> history;

public:
    Simulation(vector<double> state0)
        : state(state0) {
        window = new MainWindow(nullptr);
    }

    // Функция правой части
    vector<double> equationPN(const vector<double> &state, double dt)
    {

        vector<double> pos, speed, answer(6), accel(3);

        pos = {state[0], state[1], state[2]};
        speed = {state[3], state[4], state[5]};

        for (int i = 0; i < 3; ++i) {
            answer[i] = dt * speed[i];      // dr = v * dt
        }

        double rpos = sqrt(pos * pos);
        double rspeed = sqrt(speed * speed);
        double NewtonScal = - (G *  M) / ( pow(c, 2) * pow(rpos, 3) );

        for(int i = 0; i < 3; i++)
        {
            accel[i] = NewtonScal *
                    (pos[i] * (pow(c, 2) - 4 * G * M / rpos + rspeed * rspeed)
                     - 4 * speed[i] * (pos * speed));
        }

        for (int i = 3; i < 6; ++i) {
            answer[i] = dt * accel[i - 3];      // dv = a * dt
        }

        return answer;
    }

    // Классический метод Рунге-Кутты
    vector<double> RK4(const vector<double> &state, double dt)
    {
        vector<double> res;
        auto k1 = equationPN(state, dt);
        auto k2 = equationPN(state + (k1 * 0.5), dt);
        auto k3 = equationPN(state + (k2 * 0.5), dt);
        auto k4 = equationPN(state + k3, dt);

        res = state + (k1 + k2 * 2 + k3 * 2 + k4) / 6;

        return res;
    }

    void runSimulation(double time, double dt)
    {
        int steps = int(time / dt);
        vector<double> res = state;

        while(steps > 0)
        {
            res = RK4(res, dt);
            history.push_back(res);
            steps--;
        }
    }

    void printRes()
    {
        QScatterDataArray data;

        for(auto &state : history)
        {
            data << QVector3D(state[0], state[1], state[2]);
        }
        window->printGraph(data);
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    double dt = HOUR;
    vector<double> state0 = {48903751673.563965,    //x0
                             -70117917298.42145,    //y0
                             -86465695629.55685,    //z0
                             -25057.691331305898,   //vx0
                             6970.524886646228,     //vy0
                             24203.64291741095};    //vz0

    Simulation sim(state0);
    sim.runSimulation(HOUR * DAY * YEAR, dt);
    sim.printRes();

    return a.exec();
}

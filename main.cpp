#include "mainwindow.hpp"

#include <QApplication>
#include <bits/stdc++.h>


using namespace std;

// constants
long double G = 6.674e-11;  // gravitational constant in m^3/kg/s^2
long double c = 299792458;  //speed of light in m/s
long double M = 4e6 * 1.98847e30;  // mass of the black hole in kg

vector<double> operator * (const vector<double> &v1, const vector<double> &v2){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] += v1[i] * v2[i];
    }
    return res;
}

vector<double> operator * (const vector<double> &v1, double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] * d;
    }
    return res;
}

vector<double> operator / (const vector<double> &v1, double d){
    vector<double> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++){
        res[i] = v1[i] / d;
    }
    return res;
}

vector<double> operator - (const vector<double> &v1, const vector<double> &v2){
    vector<double> res(min(v1.size(),v2.size()));
    for (size_t i = 0; i < min(v1.size(),v2.size()); i++){
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vector<double> operator + (const vector<double> &v1, const vector<double> &v2){
    vector<double> res(min(v1.size(),v2.size()));
    for (size_t i = 0; i < min(v1.size(),v2.size()); i++){
        res[i] = v1[i] + v2[i];
    }
    return res;
}

vector<double> equationPN(const vector<double> &state, double dt)
{

    vector<double> pos, speed, answer(9);
    pos = {state[6], state[7], state[8]};
    speed = {state[3], state[4], state[5]};

    double rpos = sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
    double rspeed = sqrt(speed[0] * speed[0] + speed[1] * speed[1] + speed[2] * speed[2]);

    double NewtonScal = - (G * M) / (c * c * pow(rpos, 3));

    vector<double> first_vector = pos * (c * c - 4 * ((M * G) / rpos) + rspeed * rspeed);
    vector<double> second_vector = speed * 4;
    vector<double> third_vector = pos * speed;

    second_vector = second_vector * third_vector;
    third_vector = first_vector - second_vector;
    third_vector = third_vector * NewtonScal;

    for(size_t i = 0; i < 3; i++)
        answer[i] = third_vector[i];

                                                           // new speed (vx + ax * dt,
    for(size_t i = 3; i < 6; i++)                       // vy + ay * dt,
        answer[i] = speed[i - 3] + third_vector[i - 3] * dt; // vz + az * dt)

    third_vector = third_vector * dt;                   // new pos (x * vx + ax * dt^2/2,
    for(size_t i = 6; i < 9; i++)                       // y * vy + ay * dt^2/2, z * vz + az * dt^2/2)
        answer[i] = pos[i - 6] * speed[i - 6] + (answer[i - 6] * dt * dt) / 2;


//    for(auto & a : answer)
//        std::cout << a << " ";
//    std::cout << "\n";

    return answer;
}


class Simulation
{
private:
    vector<double> state;
    vector<vector<double>> history;
public:

    Simulation(vector<double> state0)
        : state(state0) {}

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
};




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    double x1 = 0.06759250481233711;
    double y1 = 0.04047821639956209;
    double z1 = -0.029622111319578856;
    double vx1 = 36762194899.701904;
    double vy1 = 1395427078.069418;
    double vz1 = -27363079457.16237;

    double dt = 100000;
    vector<double> state0 = {0, 0, 0, vx1, vy1, vz1, x1, y1, z1};
    Simulation sim(state0);
    auto res = sim.RK4(state0, dt);

    cout << setprecision(30);
    for(auto & a : res)
        std::cout << a << " ";
    std::cout << "\n";
//    MainWindow w;
//    w.show();
    return 0;
}

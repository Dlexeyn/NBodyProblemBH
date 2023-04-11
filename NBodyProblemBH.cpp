#include "Window_sph_graph.hpp"

#include <QApplication>
#include <bits/stdc++.h>
#include <QPointF>
#include <fstream>

using namespace std;

// constants
const double G = 6.674e-20;     // gravitational constant in km^3/kg/s^2
const double c = 300000.0;      //speed of light in km/s
const double M = 7.9556e+36;    // mass of the black hole in kg

const int HOUR = 3600;
const int DAY = 24;
const int YEAR = 365;

const int SIZE_VECTOR = 3;

const double X_BH = -16142282780211031640.09676999264;
const double Y_BH = 118611250811694902698.78585427456;
const double Z_BH = 209892887795241600000.0;

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


class Star
{
    // вектор для хранения всех позиций
    vector<vector<double>> history;

    vector<pair<double, double>> spherical_history;

    // вектор для хранения последней записи в history
    vector<double> prev_state;

public:
    Star(string name_file) {
        if(read_file(name_file))
        {
            exit(EXIT_FAILURE);
        }
    }

    /**
     * @brief read_file - функция чтения начальных данных из
     * файла для звезды
     * @param name_file - имя файла
     * @return 0 в случае успешного чтения,
     * -1 если файл невозможно открыть,
     * -2 строка в файле некорректна
     */
    int read_file(const string &name_file)
    {
        string temp_line;
        ifstream in_file(name_file);

        if(in_file.is_open())
        {
            prev_state.resize(SIZE_VECTOR * 2);
            int index = 0;
            while(getline(in_file, temp_line))
            {
                try {
                    prev_state[index++] = stod(temp_line);
                } catch (std::invalid_argument const& ex) {
                    std::cout << name_file << ": incorrect line " << index + 1 << "\n";
                    return -2;
                }

            }
        }
        else
            return -1;
        in_file.close();
        std::cout << name_file << " - correct)\n";
        return 0;
    }


    void add_state_to_history(vector<double> &new_state) { history.push_back(new_state); }

    vector<vector<double> > getHistory() const { return history; }

    vector<double> getPrev_state() const { return prev_state; }

    void setPrev_state(const vector<double> &newPrev_state) { prev_state = newPrev_state; }

    vector<pair<double, double> > getSpherical_history() const { return spherical_history; }

    void add_state_to_sph_history(pair<double, double> new_state) { spherical_history.push_back(new_state); }

};


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

        Decl -= -0.50628161876;
        RA -= 4.84765199741;

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
        QLineSeries *first = new QLineSeries();
        QLineSeries *second = new QLineSeries();
        QLineSeries *third = new QLineSeries();
        vector<QLineSeries*> data_sph = { first, second, third };
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Star S2("s2.txt");
    Star S38("s38.txt");
    Star S55("s55.txt");
    Simulation simulation(&S2, &S38, &S55, HOUR);
    simulation.runSimulation(HOUR * DAY * YEAR * 20);
    simulation.printRes();

    return a.exec();
}


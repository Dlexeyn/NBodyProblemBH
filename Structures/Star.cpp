#include "Options/Constants.h"
#include "SimulationVector.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Star {
    // вектор для хранения всех позиций
    vector<SimulationVector> history;

    // вектор для хранения RA и Decl
    vector<pair<double, double>> spherical_history_model;

    // вектор для хранения наблюдаемых величин
    vector<pair<double, pair<double, double>>> spherical_history_obs;

    int index;

    // последней запись в history
    SimulationVector prev_state;

    vector<double> init_state;

public:
    Star(string name_file)
    {
        if (read_file(name_file + ".txt")) {
            exit(EXIT_FAILURE);
        }
        if (readRA_Dcel_in_star(name_file + "_RA_Decl.txt")) {
            exit(EXIT_FAILURE);
        }

        init_state = prev_state.getX_vector();
        init_state.push_back(M_BH);

        // E matrix on 0 step
        for(size_t y = 0; y < 6; y++)
        {
            for(size_t x = 0; x < 7; x++)
            {
                if(x == y)
                {
                    prev_state.setElementDX_matrix(y, x, 1);
                }
            }
        }
    }

    void clearHistory()
    {
        history.clear();
        prev_state.setX_vector(init_state);
        spherical_history_model.clear();


        for(size_t y = 0; y < 6; y++)
        {
            for(size_t x = 0; x < 7; x++)
            {
                if(x == y)
                {
                    prev_state.setElementDX_matrix(y, x, 1);
                }
                else
                    prev_state.setElementDX_matrix(y, x, 0);
            }
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
    int read_file(const string& name_file)
    {
        double temp;
        ifstream in_file(name_file);

        prev_state.resizeX_vector(SIZE_VECTOR * 2);
        if (in_file.is_open()) {
            for (int i = 0; i < SIZE_VECTOR * 2; i++) {
                in_file >> temp;
                prev_state.setElementX_vector(i, temp);
            }
        } else
            return -1;
        in_file.close();
        std::cout << name_file << " - correct)\n";
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> findIndexModelValue()
    {
        priority_queue<int, vector<int>, greater<int>> res;
        for (size_t i = 0; i < spherical_history_obs.size(); i++) {
            res.push((int(round(spherical_history_obs[i].first * 365)) + index) % Model_Size);
        }
        return res;
    }

    int readRA_Dcel_in_star(const string& name_file)
    {
        ifstream in(name_file);
        if (in.is_open()) {
            double curDate = 0, curRA = 0, curDecl = 0;
            int n;
            in >> index >> n;
            spherical_history_obs.resize(n);
            for (int i = 0; i < n; i++) {
                in >> curDate >> curRA >> curDecl;
                spherical_history_obs[i].first = curDate;
                spherical_history_obs[i].second.first = curRA;
                spherical_history_obs[i].second.second = curDecl;
            }
            for (int i = 1; i < n; i++) {
                spherical_history_obs[i].first = spherical_history_obs[i].first - spherical_history_obs[0].first;
            }
            spherical_history_obs[0].first = 0;
        } else
            return -1;
        in.close();
        std::cout << name_file << " - correct)\n";
        return 0;
    }
    void saveHistoryToFile(string nameFile)
    {
        ofstream out(nameFile);
        if (out.is_open()){
            for(auto it: spherical_history_model){
                out<< it.first <<" "<< it.second<< endl;
            }
        }
        out.close();
//        ofstream out(nameFile);
//        if (out.is_open()) {
//            for (const auto& state : history) {
//                auto X = state.getX_vector();
//                for (size_t index = 0; index < X.size() - 1; index++) {
//                    out << X[index] << " ";
//                }
//                out << X.back() << "\n";
//            }
//        }

//        out.close();
    }
    int GetIndex()
    {
        return index;
    }

    vector<pair<double, double>> getSpherical_history_model() const
    {
        return spherical_history_model;
    }
    vector<pair<double, pair<double, double>>> getSpherical_history_obs() const
    {
        return spherical_history_obs;
    }

    void add_state_to_sph_history(pair<double, double> new_state)
    {
        spherical_history_model.push_back(new_state);
    }

    vector<SimulationVector> getHistory() const
    {
        return history;
    }

    void add_state_to_history(SimulationVector& new_state)
    {
        history.push_back(new_state);
    }

    void setPrev_state(const SimulationVector& newPrev_state)
    {
        prev_state = newPrev_state;
    }

    SimulationVector getPrev_state() const
    {
        return prev_state;
    }
    vector<double>& getInit_state()
    {
        return init_state;
    }

    void setInit_state(const vector<double>& newInit_state)
    {
        init_state = newInit_state;
    }
};

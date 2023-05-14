#include "Options/Constants.h"
#include "SimulationVector.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Star
{
    // вектор для хранения всех позиций
    vector<SimulationVector> history;
    vector<pair<double, double>> spherical_history_model;
    vector<pair<double, pair<double,double>>> spherical_history_obs;
    // вектор для хранения последней записи в history
    int index;
    SimulationVector prev_state;

public:
    Star(string name_file) {
        if(read_file(name_file+".txt") and readRA_Dcel_in_star(name_file+"_RA_Decel.txt"))
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
            prev_state.getX_vector().resize(SIZE_VECTOR * 2);
            int index = 0;
            while(getline(in_file, temp_line))
            {
                try {
                    prev_state.setElementX_vector(index++, stod(temp_line));
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
    vector<int> findIndexModelValue(){
        vector<int> res;
        res.resize(spherical_history_obs.size());
        for(int i=0;i<spherical_history_obs.size();i++){
            res[i]= (int(round(spherical_history_obs[i].first*365*24))+index)%spherical_history_model.size();
        }
    }
    int readRA_Dcel_in_star(const string &name_file)
    {
        ofstream in(name_file);
        if(in.is_open())
        {
            double curDate, curRA, curDecl;
            int n;
            in<<index<<n;
            spherical_history_obs.resize(n);
            for(int i=0;i<n;i++){
                in << curDate << curRA << curDecl;
                spherical_history_obs[i].first=curDate;
                spherical_history_obs[i].second.first=curRA;
                spherical_history_obs[i].second.second=curDecl;
            }
            for(int i=1;i<n;i++){
                spherical_history_obs[i].first-spherical_history_obs[0].first;
            }
            spherical_history_obs[0].first=0;
        }
        else
            return -1;
        in.close();
        std::cout << name_file << " - correct)\n";
        return 0;
    }
    void saveHistoryToFile(string nameFile)
    {
        if(out.is_open())
        {
            for(auto state : history)
            {
                auto X = state.getX_vector();
                for(size_t index = 0; index < X.size() - 1; index++)
                {
                    out << X[index] << " ";
                }
                out << X.back() << "\n";
            }
        }

        out.close();
    }

    vector<pair<double, double> > getSpherical_history_model() const {
        return spherical_history_model;
    }
    vector<pair<double, pair<double,double>>> getSpherical_history_obs()const{
        return spherical_history_obs;
    }

    void add_state_to_sph_history(pair<double, double> new_state) {
        spherical_history_model.push_back(new_state);
    }

    vector<SimulationVector> getHistory() const
    {
        return history;
    }

    void add_state_to_history(SimulationVector &new_state)
    {
        history.push_back(new_state);
    }

    void setPrev_state(const SimulationVector &newPrev_state)
    {
        prev_state = newPrev_state;
    }

    SimulationVector getPrev_state() const
    {
        return prev_state;
    }
};




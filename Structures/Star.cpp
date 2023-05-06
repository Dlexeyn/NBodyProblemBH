#include "Options/Constants.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

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

    void saveHistoryToFile(string nameFile)
    {
        ofstream out(nameFile);

        if(out.is_open())
        {
            for(auto state : history)
            {
                for(size_t index = 0; index < state.size() - 1; index++)
                {
                    out << state[index] << " ";
                }
                out << state.back() << "\n";
            }
        }

        out.close();
    }


    void add_state_to_history(vector<double> &new_state) { history.push_back(new_state); }

    vector<vector<double> > getHistory() const { return history; }

    vector<double> getPrev_state() const { return prev_state; }

    void setPrev_state(const vector<double> &newPrev_state) { prev_state = newPrev_state; }

    vector<pair<double, double> > getSpherical_history() const { return spherical_history; }

    void add_state_to_sph_history(pair<double, double> new_state) { spherical_history.push_back(new_state); }

};

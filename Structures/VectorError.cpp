
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


int readRA_Dcel_in_star(const string &name_file, vector<double> &date, vector<double> &RA, vector<double>&Decel)
{
    ofstream in(name_file);
    if(in.is_open())
    {
        date.clear();
        RA.clear();
        Decel.clear();
        double curDate, curRA, curDecl;
        while(in << curDate << curRA << curDecl){
            date.push_back(curDate);
            RA.push_back(curRA);
            Decel.push_back(curDecl);
        }
        for(int i=1;i<date.size();i++){
            date[i]-date[0];
        }
        date[0]=0;
    }
    else
        return -1;
    in.close();
    std::cout << name_file << " - correct)\n";
    return 0;
}

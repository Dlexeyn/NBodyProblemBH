#ifndef MODEL_HPP
#define MODEL_HPP

#include "Matrix.h"
#include "Star.cpp"

class Model
{
    Star s2;
    Star s38;
    Star s55;
//    Matrix dRA_Decl_dB;
//    Matrix dRA_Decl_dR;
//    Matrix dR_dB;
public:
    Model();
    void VectorError(vector<vector<pair<double,double>>> &error);
    Star GetS2(){
        return s2;
    }
    Star GetS38(){
        return s38;
    }
    Star GetS55(){
        return s55;
    }
};

#endif // MODEL_HPP

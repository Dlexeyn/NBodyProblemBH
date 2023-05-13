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
    void VectorError(vector<pair<double,double>> &error);
};

#endif // MODEL_HPP

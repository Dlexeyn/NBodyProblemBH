#ifndef MODELVALUE_H
#define MODELVALUE_H

#include "Matrix.h"
#include "Star.cpp"

class Model
{
    Matrix dRA_Decl_dB = Matrix(2, 7);
    Matrix dRA_Decl_dR = Matrix(2, 6);
    Matrix dR_dB = Matrix(6, 7);
public:
    Model();
    void VectorError(vector<vector<pair<double,double>>> &error);
};

#endif // MODELVALUE_H

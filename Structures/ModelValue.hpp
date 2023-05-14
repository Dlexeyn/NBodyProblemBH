#ifndef MODELVALUE_H
#define MODELVALUE_H

#include <vector>
#include "Matrix.h"
#include "Star.cpp"

class ModelValue
{
    Matrix dRA_Decl_dB = Matrix(2, 7);
    Matrix dRA_Decl_dR = Matrix(2, 6);
    Matrix dR_dB = Matrix(6, 7);

    std::vector<double> cortesian_pos;
    std::vector<double> speed;

    double RA;
    double Decl;

public:
    ModelValue();
    void VectorError(vector<vector<pair<double,double>>> &error);
    Matrix *getDRA_Decl_dR();
    std::vector<double> getCortesian_pos() const;
    std::vector<double> getSpeed() const;
};

#endif // MODELVALUE_H

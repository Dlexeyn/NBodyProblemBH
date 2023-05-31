#ifndef MODELVALUE_H
#define MODELVALUE_H

#include "Matrix.h"
#include "Star.cpp"
#include <vector>

class ModelValue {
    Matrix dRA_Decl_dR = Matrix(2, 3);

    Matrix dX_dB = Matrix(6, Size_Matrix_B);

    std::vector<long double> cortesian_pos;
    std::vector<long double> speed;

    long double RA;
    long double Decl;

public:
    ModelValue();
    std::vector<long double> getCortesian_pos() const;

    std::vector<long double> getSpeed() const;

    void setRA(long double newRA);

    void setDecl(long double newDecl);

    void setCortesian_pos(const std::vector<long double>& X_vector);

    void setSpeed(const std::vector<long double>& X_vector);

    Matrix *getDRA_Decl_dR();
    void setDRA_Decl_dR(const Matrix& newDRA_Decl_dR);

    Matrix getDX_dB() const;
    void setDX_dB(const Matrix& newDX_dB);
};

#endif // MODELVALUE_H

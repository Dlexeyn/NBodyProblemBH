#ifndef MODELVALUE_H
#define MODELVALUE_H

#include "Matrix.h"
#include "Star.cpp"
#include <vector>

class ModelValue {
    Matrix dRA_Decl_dB = Matrix(2, 7);
    Matrix dRA_Decl_dR = Matrix(2, 6);
    Matrix dR_dB = Matrix(6, 7); // dx/db

    std::vector<double> cortesian_pos;
    std::vector<double> speed;

    double RA;
    double Decl;

public:
    ModelValue();
    Matrix* getDRA_Decl_dR();
    std::vector<double> getCortesian_pos() const;
    std::vector<double> getSpeed() const;
    void setRA(double newRA);
    void setDecl(double newDecl);
    void setDR_dB(const Matrix& newDR_dB);
    void setCortesian_pos(const std::vector<double>& X_vector);
    void setSpeed(const std::vector<double>& X_vector);
    Matrix getDR_dB() const;
    void setDRA_Decl_dR(const Matrix &newDRA_Decl_dR);
};

#endif // MODELVALUE_H

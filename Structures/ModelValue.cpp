#include "ModelValue.hpp"
// #include "Star"

void ModelValue::setCortesian_pos(const std::vector<double>& X_vector)
{
    cortesian_pos.resize(SIZE_VECTOR);
    cortesian_pos[0] = X_vector[0];
    cortesian_pos[1] = X_vector[1];
    cortesian_pos[2] = X_vector[2];
}

void ModelValue::setSpeed(const std::vector<double>& X_vector)
{
    speed.resize(SIZE_VECTOR);
    speed[0] = X_vector[3];
    speed[1] = X_vector[4];
    speed[2] = X_vector[5];
}

Matrix ModelValue::getDR_dB() const
{
    return dR_dB;
}

void ModelValue::setDRA_Decl_dR(const Matrix &newDRA_Decl_dR)
{
    dRA_Decl_dR = newDRA_Decl_dR;
}

Matrix ModelValue::getDX_dB() const
{
    return dX_dB;
}

void ModelValue::setDX_dB(const Matrix &newDX_dB)
{
    dX_dB = newDX_dB;
}

ModelValue::ModelValue()
{
    cortesian_pos.resize(SIZE_VECTOR);
    speed.resize(SIZE_VECTOR);
}

Matrix* ModelValue::getDRA_Decl_dR()
{
    return &dRA_Decl_dR;
}

std::vector<double> ModelValue::getCortesian_pos() const
{
    return cortesian_pos;
}

std::vector<double> ModelValue::getSpeed() const
{
    return speed;
}

void ModelValue::setRA(double newRA)
{
    RA = newRA;
}

void ModelValue::setDecl(double newDecl)
{
    Decl = newDecl;
}

void ModelValue::setDR_dB(const Matrix& newDR_dB)
{
    dR_dB = newDR_dB;
}

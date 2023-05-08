#include "SimulationVector.hpp"

void SimulationVector::setX_vector(const std::vector<double> &newX_vector)
{
    X_vector = newX_vector;
}

void SimulationVector::clearX_vector()
{
    X_vector.clear();
    X_vector.resize(SIZE_VECTOR * 2);
}

void SimulationVector::setElementX_vector(int index, double value)
{
    X_vector[index] = value;
}

std::vector<double> SimulationVector::getX_vector() const
{
    return X_vector;
}

Matrix &SimulationVector::getdF_dr_dv()
{
    return dF_dr_dv;
}

void SimulationVector::setDF_dr_dv(const Matrix &newDF_dr_dv)
{
    dF_dr_dv = newDF_dr_dv;
}

SimulationVector::SimulationVector()
{
    X_vector.resize(SIZE_VECTOR * 2);
}





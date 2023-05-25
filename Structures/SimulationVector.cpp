#include "SimulationVector.hpp"

void SimulationVector::setX_vector(const std::vector<double>& newX_vector)
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

void SimulationVector::setElementDX_matrix(int y, int x, double value)
{
    dX__dr0_dv0_dM.setElement(y, x, value);
}

std::vector<double> SimulationVector::getX_vector() const
{
    return X_vector;
}

void SimulationVector::resizeX_vector(int new_size)
{
    X_vector.resize(new_size);
}

Matrix SimulationVector::getDX__dr0_dv0_dM() const
{
    return dX__dr0_dv0_dM;
}

void SimulationVector::setDX__dr0_dv0_dM(const Matrix& newDX__dr0_dv0_dM)
{
    dX__dr0_dv0_dM = newDX__dr0_dv0_dM;
}

SimulationVector::SimulationVector()
{
    X_vector.resize(SIZE_VECTOR * 2);
}

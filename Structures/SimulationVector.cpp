#include "SimulationVector.hpp"

const std::vector<double> &SimulationVector::getX_vector() const
{
    return X_vector;
}

void SimulationVector::setX_vector(const std::vector<double> &newX_vector)
{
    X_vector = newX_vector;
}

SimulationVector::SimulationVector()
{
    X_vector.resize(SIZE_VECTOR * 2);
}

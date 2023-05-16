#include "SimulationVector.hpp"

void SimulationVector::setX_vector(const std::vector<double>& newX_vector)
{
    X_vector = newX_vector;
}

void SimulationVector::clearX_vector()
{
    X_vector.clear();
    X_vector.resize(SIZE_VECTOR * 2 + 1);
}

void SimulationVector::setElementX_vector(int index, double value)
{
    X_vector[index] = value;
}

std::vector<double> SimulationVector::getX_vector() const
{
    return X_vector;
}

void SimulationVector::resizeX_vector(int new_size)
{
    X_vector.resize(new_size);
}

Matrix SimulationVector::getDX_dB() const
{
    return dX_dB;
}

void SimulationVector::setDX_dB(const Matrix& newDX_dB)
{
    dX_dB = newDX_dB;
}

Matrix SimulationVector::getDF_dX() const
{
    return dF_dX;
}

void SimulationVector::setDF_dX(const Matrix& newDF_dX)
{
    dF_dX = newDF_dX;
}

SimulationVector::SimulationVector()
{
    X_vector.resize(SIZE_VECTOR * 2);

    // dX_dB = E + 0-ой столбец
    for (int i = 0; i < dX_dB.Get_sizeN(); i++)
        for (int j = 0; j < dX_dB.Get_sizeM(); j++) {
            if (i == j)
                dX_dB.setElement(i, j, 1);
        }
}

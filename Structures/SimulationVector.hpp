#ifndef SIMULATIONVECTOR_HPP
#define SIMULATIONVECTOR_HPP

#include "Matrix.h"
#include "Options/Constants.h"
#include "VectorsOperations.hpp"
#include <vector>

class SimulationVector {
    std::vector<double> X_vector;

    Matrix dX_dB = Matrix(6, 7);

    Matrix dF_dX = Matrix(6, 6);

public:
    SimulationVector();

    void setX_vector(const std::vector<double>& newX_vector);

    void clearX_vector();

    void setElementX_vector(int index, double value);

    std::vector<double> getX_vector() const;

    void resizeX_vector(int new_size);

    friend SimulationVector operator+(const SimulationVector& V1, const SimulationVector& V2)
    {
        SimulationVector res;
        res.setX_vector(V1.getX_vector() + V2.getX_vector());
        res.setDF_dX(V1.dF_dX + V2.dF_dX);
        res.setDX_dB(V1.dX_dB + V2.dX_dB);
        return res;
    }

    friend SimulationVector operator*(const double num, const SimulationVector& V)
    {
        SimulationVector res;
        res.setX_vector(num * V.getX_vector());
        res.setDF_dX(num * V.dF_dX);
        res.setDX_dB(num * V.dX_dB);
        return res;
    }

    friend SimulationVector operator/(const SimulationVector& V, const double num)
    {
        SimulationVector res;
        res.setX_vector(V.getX_vector() / num);
        res.setDF_dX(V.dF_dX / num);
        res.setDX_dB(V.dX_dB / num);
        return res;
    }

    SimulationVector& operator=(const SimulationVector& V)
    {
        setDX_dB(V.getDX_dB());
        setDF_dX(V.getDF_dX());
        X_vector = V.getX_vector();
        return *this;
    }

    Matrix getDX_dB() const;

    void setDX_dB(const Matrix& newDX_dB);

    Matrix getDF_dX() const;

    void setDF_dX(const Matrix& newDF_dX);
};

#endif // SIMULATIONVECTOR_HPP

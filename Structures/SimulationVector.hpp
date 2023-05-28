#ifndef SIMULATIONVECTOR_HPP
#define SIMULATIONVECTOR_HPP

#include "Matrix.h"
#include "Options/Constants.h"
#include "VectorsOperations.hpp"
#include <vector>

class SimulationVector {
    std::vector<double> X_vector;

    Matrix dX__dr0_dv0_dM = Matrix(6, 7);

public:
    SimulationVector();

    void setX_vector(const std::vector<double>& newX_vector);

    void clearX_vector();

    void setElementX_vector(int index, double value);

    void setElementDX_matrix(int y, int x, double value);

    std::vector<double> getX_vector() const;

    void resizeX_vector(int new_size);

    friend SimulationVector operator+(const SimulationVector& V1, const SimulationVector& V2)
    {
        SimulationVector res;
        res.setX_vector(V1.getX_vector() + V2.getX_vector());
        res.setDX__dr0_dv0_dM(V1.dX__dr0_dv0_dM + V2.dX__dr0_dv0_dM);
        return res;
    }

    friend SimulationVector operator*(const double num, const SimulationVector& V)
    {
        SimulationVector res;
        res.setX_vector(num * V.getX_vector());
        res.setDX__dr0_dv0_dM(num * V.dX__dr0_dv0_dM);
        return res;
    }

    friend SimulationVector operator/(const SimulationVector& V, const double num)
    {
        SimulationVector res;
        res.setX_vector(V.getX_vector() / num);
        res.setDX__dr0_dv0_dM(V.dX__dr0_dv0_dM / num);
        return res;
    }

    SimulationVector& operator=(const SimulationVector& V)
    {
        X_vector = V.getX_vector();
        setDX__dr0_dv0_dM(V.getDX__dr0_dv0_dM());
        return *this;
    }

    Matrix getDX__dr0_dv0_dM() const;

    void setDX__dr0_dv0_dM(const Matrix& newDX__dr0_dv0_dM);
};

#endif // SIMULATIONVECTOR_HPP

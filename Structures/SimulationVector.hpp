#ifndef SIMULATIONVECTOR_HPP
#define SIMULATIONVECTOR_HPP

#include <vector>
#include "Options/Constants.h"
#include "VectorsOperations.hpp"
#include "Matrix.h"

class SimulationVector
{
    std::vector<double> X_vector;
    Matrix dF_dr_dv = Matrix(6, 6);

public:
    SimulationVector();

    void setX_vector(const std::vector<double> &newX_vector);

    void clearX_vector();

    void setElementX_vector(int index, double value);

    std::vector<double> getX_vector() const;

    Matrix& getdF_dr_dv();

    void setDF_dr_dv(const Matrix &newDF_dr_dv);

    friend SimulationVector operator+(const SimulationVector& V1, const SimulationVector& V2)
    {
        SimulationVector res;
        res.setX_vector(V1.getX_vector() + V2.getX_vector());
        res.setDF_dr_dv(V1.dF_dr_dv + V2.dF_dr_dv);
        return res;
    }

    friend SimulationVector operator*(const double num, const SimulationVector& V)
    {
        SimulationVector res;
        res.setX_vector(num * V.getX_vector());
        res.setDF_dr_dv(num * V.dF_dr_dv);
        return res;
    }

    friend SimulationVector operator/(const SimulationVector& V, const double num)
    {
        SimulationVector res;
        res.setX_vector(V.getX_vector() / num);
        res.setDF_dr_dv(V.dF_dr_dv / num);
        return res;
    }

};

#endif // SIMULATIONVECTOR_HPP

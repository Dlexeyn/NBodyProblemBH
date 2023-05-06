#ifndef SIMULATIONVECTOR_HPP
#define SIMULATIONVECTOR_HPP

#include <vector>
#include "Options/Constants.h"

class SimulationVector
{
    std::vector<double> X_vector;
    //
public:
    SimulationVector();
    const std::vector<double> &getX_vector() const;
    void setX_vector(const std::vector<double> &newX_vector);
};

#endif // SIMULATIONVECTOR_HPP

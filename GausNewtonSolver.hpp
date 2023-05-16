#ifndef GAUSNEWTONSOLVER_H
#define GAUSNEWTONSOLVER_H
#include "Structures/ModelValue.hpp"

class GausNewtonSolver {
public:
    GausNewtonSolver();

    void calculate_dRA_Decl_dR(ModelValue& current_value);

    SimulationVector Gauss_Newton(SimulationVector x0, Matrix& A, Matrix& R);

    Matrix solve_system(Matrix& gradient_f, Matrix& f_b);
};

#endif // GAUSNEWTONSOLVER_H

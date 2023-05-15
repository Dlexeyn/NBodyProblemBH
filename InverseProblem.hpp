#ifndef INVERSEPROBLEM_HPP
#define INVERSEPROBLEM_HPP
#include "Structures/ModelValue.hpp"

class InverseProblem {
public:
    InverseProblem();

    void calculate_dRA_Decl_dR(ModelValue& current_value);

    //@todo
    SimulationVector Gauss_Newton(SimulationVector x0, Matrix& A, Matrix& R);
    Matrix solve_system(Matrix& gradient_f, Matrix& f_b);
};

#endif // INVERSEPROBLEM_HPP

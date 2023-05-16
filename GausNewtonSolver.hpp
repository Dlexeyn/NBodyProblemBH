#ifndef GAUSNEWTONSOLVER_H
#define GAUSNEWTONSOLVER_H
#include "Structures/ModelValue.hpp"

class GausNewtonSolver {
public:
    GausNewtonSolver();

    void calculate_dRA_Decl_dR(ModelValue& current_value);
    void calculate_dr_db(ModelValue& current_value);


    vector<double> Gauss_Newton(vector<double> x0, Matrix& A, Matrix& R);

    Matrix solve_system(Matrix& gradient_f, Matrix& f_b);
};

#endif // GAUSNEWTONSOLVER_H

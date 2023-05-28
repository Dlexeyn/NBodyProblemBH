#include "GausNewtonSolver.hpp"

GausNewtonSolver::GausNewtonSolver()
{
}

void GausNewtonSolver::calculate_dRA_Decl_dR(ModelValue& current_value)
{

    double x = current_value.getCortesian_pos()[0];
    double y = current_value.getCortesian_pos()[1];
    double z = current_value.getCortesian_pos()[2];

    double RA_denomerator = x * x + y * y;
    current_value.getDRA_Decl_dR()->setElement(0, 0, -y / RA_denomerator); // dRA/dx
    current_value.getDRA_Decl_dR()->setElement(0, 1, x / RA_denomerator); // dRA/dy
    current_value.getDRA_Decl_dR()->setElement(0, 2, 0); // dRA/dz

    double Decl_denomerator = (x * x + y * y + z * z) * sqrt(RA_denomerator);

    current_value.getDRA_Decl_dR()->setElement(1, 0, -(x * z) / Decl_denomerator); // dDecl/dx
    current_value.getDRA_Decl_dR()->setElement(1, 1, (y * z) / Decl_denomerator); // dDecl/dy
    current_value.getDRA_Decl_dR()->setElement(1, 2, RA_denomerator / Decl_denomerator); // dDecl/dz

}


vector<double> GausNewtonSolver::Gauss_Newton(vector<double> &x0, Matrix& A, Matrix& R)
{

    Matrix gradient_f = (A.Transposition() * A);
    Matrix f_b = (A.Transposition() * R);
    Matrix solution_system = solve_system(gradient_f, f_b);

    vector<double> new_x0;
    new_x0.resize(SIZE_VECTOR * 2 + 1);
    for (int i = 0; i < 7; i++) {
        new_x0[i] = x0[i] - solution_system.Get_matrix()[i][0];
    }
    return new_x0;
}

Matrix GausNewtonSolver::solve_system(Matrix& gradient_f, Matrix& f_b)
{
    Matrix L = f_b.Cholesky_decomposition(gradient_f);

    Matrix y(L.Get_sizeN(), f_b.Get_sizeM());

    for (int i = 0; i < L.Get_sizeN(); i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L.Get_matrix()[i][j] * y.Get_matrix()[j][0];
        }
        if (L.Get_matrix()[i][i] == 0) {
            y.setElement(i, 0, 0);
        } else {
            y.setElement(i, 0, (f_b.Get_matrix()[i][0] - sum) / L.Get_matrix()[i][i]);
        }
    }

    L = L.Transposition();

    Matrix solution_system(L.Get_sizeN(), y.Get_sizeM());

    for (int i = L.Get_sizeN() - 1; i > -1; i--) {
        double sum = 0;
        for (int j = i; j < L.Get_sizeN(); j++) {
            sum += L.Get_matrix()[i][j] * solution_system.Get_matrix()[j][0];
        }
        if (L.Get_matrix()[i][i] == 0) {
            solution_system.setElement(i, 0, 0);
        } else {
            solution_system.setElement(i, 0, (y.Get_matrix()[i][0] - sum) / L.Get_matrix()[i][i]);
        }
    }

    return solution_system;
}

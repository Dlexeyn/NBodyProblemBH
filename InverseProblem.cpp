#include "InverseProblem.hpp"

InverseProblem::InverseProblem()
{
}

void InverseProblem::calculate_dRA_Decl_dR(ModelValue& current_value)
{
    auto dRA_Decl_dR = current_value.getDRA_Decl_dR()->Get_matrix();

    double x = current_value.getCortesian_pos()[0];
    double y = current_value.getCortesian_pos()[1];
    double z = current_value.getCortesian_pos()[2];

    double RA_denomerator = x * x + y * y;
    dRA_Decl_dR[0][0] = -y / RA_denomerator; // dRA/dx
    dRA_Decl_dR[0][1] = x / RA_denomerator; // dRA/dy
    dRA_Decl_dR[0][2] = 0; // dRA/dz

    double Decl_denomerator = (x * x + y * y + z * z) * sqrt(RA_denomerator);

    dRA_Decl_dR[1][0] = -(x * z) / Decl_denomerator; // dDecl/dx
    dRA_Decl_dR[1][1] = (y * z) / Decl_denomerator; // dDecl/dy
    dRA_Decl_dR[1][2] = RA_denomerator / Decl_denomerator; // dDecl/dz
}

SimulationVector InverseProblem::Gauss_Newton(SimulationVector x0, Matrix& A, Matrix& R)
{

    Matrix gradient_f = (A.Transposition() * A);
    Matrix f_b = (A.Transposition() * R); // f(^b) is vector 6x1
    Matrix solution_system = solve_system(gradient_f, f_b);

    SimulationVector new_x0;
    for (int i = 0; i < 6; i++) {
        new_x0.getX_vector()[i] = x0.getX_vector()[0] - solution_system.Get_matrix()[i][0];
    }
    return new_x0;
}

Matrix InverseProblem::solve_system(Matrix& gradient_f, Matrix& f_b)
{
    Matrix decomposed_matrix = f_b.Cholesky_decomposition(gradient_f);

    Matrix y(decomposed_matrix.Get_sizeN(), f_b.Get_sizeM()); // find y

    for (int i = 0; i < decomposed_matrix.Get_sizeN(); i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += decomposed_matrix.Get_matrix()[i][j] * y.Get_matrix()[j][0];
        }
        if (decomposed_matrix.Get_matrix()[i][i] == 0) {
            y.Get_matrix()[i][0] = 0;
        } else {
            y.Get_matrix()[i][0] = (f_b.Get_matrix()[i][0] - sum) / decomposed_matrix.Get_matrix()[i][i];
        }
    }

    decomposed_matrix = decomposed_matrix.Transposition(); // find x0

    Matrix solution_system(decomposed_matrix.Get_sizeN(), y.Get_sizeM());

    for (int i = decomposed_matrix.Get_sizeN() - 1; i > -1; i--) {
        double sum = 0;
        for (int j = i; j < decomposed_matrix.Get_sizeN(); j++) {
            sum += decomposed_matrix.Get_matrix()[i][j] * solution_system.Get_matrix()[j][0];
        }
        if (decomposed_matrix.Get_matrix()[i][i] == 0) {
            solution_system.Get_matrix()[i][0] = 0;
        } else {
            solution_system.Get_matrix()[i][0] = (y.Get_matrix()[i][0] - sum) / decomposed_matrix.Get_matrix()[i][i];
        }
    }

    return solution_system;
}

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

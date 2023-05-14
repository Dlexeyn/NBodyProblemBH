#ifndef INVERSEPROBLEM_HPP
#define INVERSEPROBLEM_HPP
#include "Structures/ModelValue.hpp"

class InverseProblem
{
public:
    InverseProblem();

    void calculate_dRA_Decl_dR(ModelValue &current_value);

    //@todo
    void Gauss_Newton();
};

#endif // INVERSEPROBLEM_HPP

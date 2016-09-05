#pragma once

#include <string>

#include "cube/cube.hpp"
#include "cube_sol.hpp"

class CubeProblem
{
public:
    Cube cube;
    std::string instance_name;
    bool is_loaded;

    CubeProblem();
    ~CubeProblem();

    void evalSolution( CubeSolution& sol );
};


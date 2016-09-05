#include "cube_prob.hpp"

CubeProblem::CubeProblem()
{}

CubeProblem::~CubeProblem()
{}

void CubeProblem::evalSolution( CubeSolution & sol )
{
    // TODO: Evaluate a solution
}

void CubeProblem::load( std::string & file )
{
    this->cube.readFromFile( file );
    this->is_loaded = true;
}

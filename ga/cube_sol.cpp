#include "cube_sol.hpp"

CubeSolution::CubeSolution()
{
    for( int i = 0; i < _NUM_MOVES; ++i )
        this->moves[ i ] = _NAM;

    this->fitness = 0;
}

CubeSolution::~CubeSolution()
{}

bool CubeSolution::operator<( const CubeSolution & other )
{
    return this->fitness < other.fitness;
}

bool CubeSolution::operator<=( const CubeSolution & other )
{
    return this->fitness <= other.fitness;
}

bool CubeSolution::operator>( const CubeSolution & other )
{
    return this->fitness > other.fitness;
}

bool CubeSolution::operator>=( const CubeSolution & other )
{
    return this->fitness >= other.fitness;
}

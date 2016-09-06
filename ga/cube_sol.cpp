#include "cube_sol.hpp"

CubeSolution::CubeSolution()
{
    for( int i = 0; i < CubeSolution::NUM_MOVES; ++i )
        this->moves[ i ] = CubeSolution::NAM;

    this->fitness = 0;
}

CubeSolution::CubeSolution( const CubeSolution & other )
{
    for( int i = 0; i < CubeSolution::NUM_MOVES; ++i )
        this->moves[ i ] = other.moves[ i ];

    this->fitness = other.fitness;
}

CubeSolution::~CubeSolution()
{}

CubeSolution & CubeSolution::operator=( const CubeSolution & other )
{
    for( int i = 0; i < CubeSolution::NUM_MOVES; ++i )
        this->moves[ i ] = other.moves[ i ];

    this->fitness = other.fitness;

    return *this;
}

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

bool CubeSolution::operator==( const CubeSolution & other )
{
    return this->fitness == other.fitness;
}

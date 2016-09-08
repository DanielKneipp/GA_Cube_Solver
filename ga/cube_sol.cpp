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

bool CubeSolution::operator<( const CubeSolution & other ) const
{
    return this->fitness < other.fitness;
}

bool CubeSolution::operator<=( const CubeSolution & other ) const
{
    return this->fitness <= other.fitness;
}

bool CubeSolution::operator>( const CubeSolution & other ) const
{
    return this->fitness > other.fitness;
}

bool CubeSolution::operator>=( const CubeSolution & other ) const
{
    return this->fitness >= other.fitness;
}

bool CubeSolution::operator==( const CubeSolution & other ) const
{
    return this->fitness == other.fitness;
}

std::string CubeSolution::toString() const
{
    std::string str( std::to_string( this->fitness ) );
    for( unsigned i = 0; i < CubeSolution::NUM_MOVES; ++i )
        str += std::to_string( this->moves[ i ] ) + " ";

    return str;
}

void CubeSolution::moveNAMtoTheEnd()
{
    bool after_NAM = false;
    for( unsigned i = 0, j = 0; i < CubeSolution::NUM_MOVES; ++i )
    {
        if( this->moves[ i ] != CubeSolution::NAM )
        {
            if( after_NAM )
            {
                this->moves[ j ] = this->moves[ i ];
                this->moves[ i ] = CubeSolution::NAM;
                after_NAM = false;
                j = i;
            }

            ++j;
        }
        else
        {
            after_NAM = true;
        }
    }
}

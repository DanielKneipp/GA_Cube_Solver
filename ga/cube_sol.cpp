#include "cube_sol.hpp"

#include <vector>

#include "cube/cube.hpp"

#include "ga/utils.hpp"

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

CubeSolution::CubeSolution( CubeSolution && other )
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

CubeSolution & CubeSolution::operator=( CubeSolution && other )
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
    std::string str( std::to_string( this->fitness ) + " __ " );
    for( unsigned i = 0; i < CubeSolution::NUM_MOVES; ++i )
        str += std::to_string( this->moves[ i ] ) + " ";

    return str;
}

std::string CubeSolution::toString( unsigned cube_num_moves ) const
{
    std::string str( std::to_string( this->fitness ) + " __ " );
    for( unsigned i = 0; i < CubeSolution::NUM_MOVES; ++i )
    {
        if( this->moves[ i ] > ( int )cube_num_moves )
        {
            unsigned s_m_idx = this->moves[ i ] - cube_num_moves;
            std::vector< uint > smart_moves = SmartMoves::getMove( s_m_idx );
            for( uint & s_m : smart_moves )
                str += std::to_string( s_m ) + " ";
        }
        else
        {
            str += std::to_string( this->moves[ i ] ) + " ";
        }
    }

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
            }
            ++j;
        }
        else
        {
            if( !after_NAM )
                after_NAM = true;
        }
    }
}

void CubeSolution::moveNAMtoTheBeginning()
{
    bool after_NAM = false;
    for( 
        int i = ( int )CubeSolution::NUM_MOVES, j = ( int )CubeSolution::NUM_MOVES; 
        i >= 0; 
        --i 
    )
    {
        if( this->moves[ i ] != CubeSolution::NAM )
        {
            if( after_NAM )
            {
                this->moves[ j ] = this->moves[ i ];
                this->moves[ i ] = CubeSolution::NAM;
            }
            --j;
        }
        else
        {
            if( !after_NAM )
                after_NAM = true;
        }
    }
}

void CubeSolution::sortNAMPositions()
{
    unsigned NAM_count = 0;
    std::vector< std::size_t > pos( CubeSolution::NUM_MOVES );
    int old_moves[ CubeSolution::NUM_MOVES ];

    for( std::size_t i = 0; i < CubeSolution::NUM_MOVES; ++i )
    {
        old_moves[ i ] = this->moves[ i ];
        this->moves[ i ] = -2;
        pos[ i ] = i;
        if( old_moves[ i ] == CubeSolution::NAM )
            ++NAM_count;
    }
    
    for( unsigned i = 0; i < NAM_count; ++i )
    {
        std::size_t p = genIntRandNumber< std::size_t >( 0, pos.size() - 1 );
        this->moves[ pos[ p ] ] = CubeSolution::NAM;
        pos.erase( pos.begin() + p );
    }

    for( unsigned i = 0, j = 0; i < CubeSolution::NUM_MOVES; ++i )
    {
        while( j < CubeSolution::NUM_MOVES && old_moves[ j ] == CubeSolution::NAM )
            ++j;
        if( this->moves[ i ] != CubeSolution::NAM )
            this->moves[ i ] = old_moves[ j++ ];
    }
}

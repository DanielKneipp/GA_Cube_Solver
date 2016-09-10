#pragma once

#include <string>

class CubeSolution
{
public:
    static const unsigned NUM_MOVES = 100;
    /// <summary> Not a move </summary>
    static const int NAM = -1;

    int moves[ CubeSolution::NUM_MOVES ];
    float fitness;

    CubeSolution();
    CubeSolution( const CubeSolution & other );
    CubeSolution( CubeSolution && other );
    ~CubeSolution();

    CubeSolution & operator = ( const CubeSolution & other );
    CubeSolution & operator = ( CubeSolution && other );
    bool operator < ( const CubeSolution & other ) const;
    bool operator <= ( const CubeSolution & other ) const;
    bool operator > ( const CubeSolution & other ) const;
    bool operator >= ( const CubeSolution & other ) const;
    bool operator == ( const CubeSolution & other ) const;
    std::string toString() const;
    std::string toString( unsigned cube_num_moves ) const;

    void moveNAMtoTheEnd();
    void moveNAMtoTheBeginning();
    void sortNAMPositions();
};
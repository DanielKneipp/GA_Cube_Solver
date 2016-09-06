#pragma once

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
    ~CubeSolution();


    CubeSolution & operator = ( const CubeSolution & other );
    bool operator < ( const CubeSolution & other );
    bool operator <= ( const CubeSolution & other );
    bool operator > ( const CubeSolution & other );
    bool operator >= ( const CubeSolution & other );
    bool operator == ( const CubeSolution & other );
};
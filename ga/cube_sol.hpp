#pragma once

#define _NUM_MOVES 100
#define _NAM -1 // Not a move

class CubeSolution
{
public:
    static const unsigned NUM_MOVES = 100;
    /// <summary> Not a move </summary>
    static const int NAM = -1;

    int moves[ _NUM_MOVES ];
    float fitness;

    CubeSolution();
    ~CubeSolution();

    bool operator < ( const CubeSolution & other );
    bool operator <= ( const CubeSolution & other );
    bool operator > ( const CubeSolution & other );
    bool operator >= ( const CubeSolution & other );
};
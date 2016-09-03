#pragma once

#include <string>

#include "matrix.hpp"

struct Face
{
    static const ushort _NUM_CUBE_FACES = 6;
    const enum TYPES
    {
        FRONT,
        BACK,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
};

class Cube
{
public:
    uint size;
    Array2D< char > cube[ Face::_NUM_CUBE_FACES ];

    Cube();
    Cube( uint s );
    Cube( const Cube & other ); // Clones the other object
    Cube( Cube && other );
    ~Cube();
    Cube& operator=( const Cube & other );
    Cube& operator=( Cube && other );
    void create( uint size );
    void clear();
    void readFromFile( std::string&& f );
    void copyTo( Cube& other ) const;
    void makeMove( uint move );
    std::string getString();

private:
    uint num_moves;
    char * move_aux_arr;

    void rotateF90( uint level );
    void rotateF90i( uint level );
    void rotateF180( uint level );
    void rotateB90( uint level );
    void rotateU90( uint level );
    void rotateD90( uint level );
    void rotateL90( uint level );
    void rotateR90( uint level );
};

struct Move
{
    static const ushort _NUM_MOVE_TYPES = 3;
    const enum TYPES
    {
        ROT90,
        ROT90I,
        ROT180
    };

    static uint generate( uint cube_size )
    {
        // if a number k is odd, than it has the same number
        // of movements as the k-1 number
        uint s_aux;
        if( cube_size % 2 > 0 )
            s_aux = cube_size - 1;

        uint levels = s_aux / 2;

        // Each face (which is in a level) has 3 possible moves
        return Face::_NUM_CUBE_FACES * Move::_NUM_MOVE_TYPES * levels;
    }
};
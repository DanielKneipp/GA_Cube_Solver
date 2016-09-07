#pragma once

#include <string>
#include <stdexcept>

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

    static TYPES getRightOf( TYPES face )
    {
        switch( face )
        {
        case TYPES::FRONT:
            return TYPES::RIGHT;
        case TYPES::RIGHT:
            return TYPES::BACK;
        case TYPES::BACK:
            return TYPES::LEFT;
        case TYPES::LEFT:
            return TYPES::FRONT;
        case TYPES::UP:
            return TYPES::RIGHT;
        case TYPES::DOWN:
            return TYPES::RIGHT;
        default:
            return face;
        }
    }

    static TYPES getLeftOf( TYPES face )
    {
        switch( face )
        {
        case TYPES::FRONT:
            return TYPES::LEFT;
        case TYPES::RIGHT:
            return TYPES::FRONT;
        case TYPES::BACK:
            return TYPES::RIGHT;
        case TYPES::LEFT:
            return TYPES::BACK;
        case TYPES::UP:
            return TYPES::LEFT;
        case TYPES::DOWN:
            return TYPES::LEFT;
        default:
            return face;
        }
    }

    static TYPES getUpOf( TYPES face )
    {
        switch( face )
        {
        case TYPES::FRONT:
            return TYPES::UP;
        case TYPES::RIGHT:
            return TYPES::UP;
        case TYPES::BACK:
            return TYPES::UP;
        case TYPES::LEFT:
            return TYPES::UP;
        case TYPES::UP:
            return TYPES::BACK;
        case TYPES::DOWN:
            return TYPES::FRONT;
        default:
            return face;
        }
    }

    static TYPES getDownOf( TYPES face )
    {
        switch( face )
        {
        case TYPES::FRONT:
            return TYPES::DOWN;
        case TYPES::RIGHT:
            return TYPES::DOWN;
        case TYPES::BACK:
            return TYPES::DOWN;
        case TYPES::LEFT:
            return TYPES::DOWN;
        case TYPES::UP:
            return TYPES::FRONT;
        case TYPES::DOWN:
            return TYPES::BACK;
        default:
            return face;
        }
    }

    static TYPES getFrontOf( TYPES face )
    {
        return face;
    }

    static TYPES getBackOf( TYPES face )
    {
        switch( face )
        {
        case TYPES::FRONT:
            return TYPES::BACK;
        case TYPES::RIGHT:
            return TYPES::LEFT;
        case TYPES::BACK:
            return TYPES::FRONT;
        case TYPES::LEFT:
            return TYPES::RIGHT;
        case TYPES::UP:
            return TYPES::DOWN;
        case TYPES::DOWN:
            return TYPES::UP;
        default:
            return face;
        }
    }
};

class Cube
{
public:
    uint size;
    uint num_moves;
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
    void readFromFile( const std::string& f );
    void copyTo( Cube& other ) const;
    void makeMove( uint move );
    std::string getString();
    bool isSolved();

private:
    char * move_aux_arr;
    bool is_solved;
    bool is_solved_updated;

    void rotateF90( uint level );
    void rotateF90i( uint level ); // disabled
    void rotateF180( uint level ); // disabled
    void rotateB90( uint level );
    void rotateU90( uint level );
    void rotateD90( uint level );
    void rotateL90( uint level );
    void rotateR90( uint level );
};

struct Move
{
    static const ushort NUM_MOVE_TYPES = 3;
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
        uint s_aux = cube_size;
        if( cube_size % 2 > 0 )
            s_aux--;

        uint levels = s_aux / 2;

        // Each face (which is in a level) has 3 possible moves
        return Face::_NUM_CUBE_FACES * Move::NUM_MOVE_TYPES * levels;
    }
};
#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

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

    static const uint NUM_SPINS = 4;
    const enum SPIN
    {
        NOP,
        CW,
        CW2,
        CCW,
    };

    static TYPES getRightOf( TYPES face, Face::SPIN spin = Face::SPIN::NOP )
    {
        switch( spin )
        {
        case Face::SPIN::NOP:
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
        case Face::SPIN::CW:
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
        case Face::SPIN::CCW:
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
        case Face::SPIN::CW2:
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
        default:
            return face;
        }
    }

    static TYPES getLeftOf( TYPES face, Face::SPIN spin = Face::SPIN::NOP )
    {
        switch( spin )
        {
        case Face::SPIN::NOP:
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
        case Face::SPIN::CW:
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
        case Face::SPIN::CCW:
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
        case Face::SPIN::CW2:
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
        default:
            return face;
        }
    }

    static TYPES getUpOf( TYPES face, Face::SPIN spin = Face::SPIN::NOP )
    {
        switch( spin )
        {
        case Face::SPIN::NOP:
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
        case Face::SPIN::CW:
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
        case Face::SPIN::CCW:
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
        case Face::SPIN::CW2:
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
        default:
            return face;
        }
    }

    static TYPES getDownOf( TYPES face, Face::SPIN spin = Face::SPIN::NOP )
    {
        switch( spin )
        {
        case Face::SPIN::NOP:
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
        case Face::SPIN::CW:
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
        case Face::SPIN::CCW:
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
        case Face::SPIN::CW2:
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

struct SmartMoves
{
    const enum TYPES
    {
        /// Two edge flip cw (clockwise)
        T_E_F_CW,
        /// Two edge flip ccw (counterclockwise)
        T_E_F_CCW,
        /// Two corner flip cw
        T_C_F_CW,
        /// Two corner flip ccw
        T_C_F_CCW,
        /// Two edge swap cw
        T_E_S_CW,
        /// Two edge swap ccw
        T_E_S_CCW,
        /// Two edge/corner swap cw
        T_EC_S_CW,
        /// Two edge/corner swap ccw
        T_EC_S_CCW,
        /// Three corner swap cw
        T_C_S_CW,
        /// Three corner swap ccw
        T_C_S_CCW,
        /// Three inslice edge swap cw
        T_I_E_S_CW,
        /// Three inslice edge swap ccw
        T_I_E_S_CCW
    };

    static const uint NUM_MOVE_TYPES = 12;
    /// Mirroring operation makes the move space twice bigger.
    static const uint MIRROR_OP = 2;
    /// 12 (number of default smart moves) * 2 (mirroring) * 4 (spins)
    /// * 6 (number of faces that could be the front)
    static const uint NUM_MOVES_PER_LEVEL = 576;

    static std::vector< uint > getDefaultMove( TYPES type )
    {
        switch( type )
        {
            /// [F R B L U L' U B' R' F' L' U' L U']
        case SmartMoves::T_E_F_CW:
            return{ 0, 5, 1, 4, 2, 10, 2, 7, 11, 6, 10, 8, 4, 8 };

            /// [F' L' B' R' U' R U' B L F R U R' U]
        case SmartMoves::T_E_F_CCW:
            return{ 6, 10, 7, 11, 8, 5, 8, 1, 4, 0, 5, 2, 11, 2 };

            /// [L D' L' F' D' F U F' D F L D L' U'] only works on level 0
        case SmartMoves::T_C_F_CW:
            return{ 4, 9, 10, 6, 9, 0, 2, 6, 3, 0, 4, 3, 10, 8 };

            /// [R' D R F D F' U' F D' F' R' D' R U] only works on level 0
        case SmartMoves::T_C_F_CCW:
            return{ 11, 3, 5, 0, 3, 6, 8, 0, 9, 6, 11, 9, 5, 2 };

            /// [U F2 U' R' D' L' F2 L D R]
        case SmartMoves::T_E_S_CW:
            return{ 2, 12, 8, 11, 9, 10, 12, 4, 3, 5 };

            /// [U' F2 U L D R F2 R' D' L']
        case SmartMoves::T_E_S_CCW:
            return{ 8, 12, 2, 4, 3, 5, 12, 11, 9, 10 };

            /// [R' U R U' R' U F R B' R B R F' R2]
        case SmartMoves::T_EC_S_CW:
            return{ 11, 2, 5, 8, 11, 2, 0, 5, 7, 5, 1, 5, 6, 17 };

            /// [L U' L' U L U' F' L' B L' B' L' F L2]
        case SmartMoves::T_EC_S_CCW:
            return{ 4, 8, 10, 2, 4, 8, 6, 10, 1, 10, 7, 10, 0, 16 };

            /// [F' U B U' F U B' U'] only works on level 0
        case SmartMoves::T_C_S_CW:
            return{ 6, 2, 1, 8, 0, 2, 7, 8 };

            /// [F U' B' U F' U' B U] only works on level 0
        case SmartMoves::T_C_S_CCW:
            return{ 0, 8, 7, 2, 6, 8, 1, 2 };

            /// [R L' U2 R' L F2]
        case SmartMoves::T_I_E_S_CW:
            return{ 5, 10, 2, 11, 4, 12 };

            /// [L' R U2 L R' F2]
        case SmartMoves::T_I_E_S_CCW:
            return{ 10, 5, 14, 4, 11, 12 };

        default:
            return std::vector< uint >();
        }
    }

    static uint getNumSmartMoves( uint cube_size )
    {
        uint n_levels = cube_size / 2;
        return SmartMoves::NUM_MOVES_PER_LEVEL * n_levels;
    }

    static std::vector< uint > getMove( uint m )
    {
        uint mirrored = m % SmartMoves::MIRROR_OP;
        uint spin = ( m / SmartMoves::MIRROR_OP ) % Face::NUM_SPINS;
        uint move_type = ( m / SmartMoves::MIRROR_OP / Face::NUM_SPINS ) % SmartMoves::NUM_MOVE_TYPES;
        uint face = ( m / SmartMoves::MIRROR_OP / Face::NUM_SPINS / SmartMoves::NUM_MOVE_TYPES ) % Face::_NUM_CUBE_FACES;
        uint level = 0;

        // This movements don't make any difference on the individual genotype if the level > 0
        if( move_type != SmartMoves::T_C_F_CW && move_type != SmartMoves::T_C_F_CCW &&
            move_type != SmartMoves::T_C_S_CW && move_type != SmartMoves::T_C_S_CCW )
        {
            level = m / ( SmartMoves::NUM_MOVE_TYPES * Face::NUM_SPINS * SmartMoves::MIRROR_OP * Face::_NUM_CUBE_FACES );
        }

        std::vector< uint > moves = SmartMoves::getDefaultMove( ( SmartMoves::TYPES )move_type );

        uint move_level_shift = SmartMoves::NUM_MOVES_PER_LEVEL * level;

        for( uint & move : moves )
        {
            if( face != Face::TYPES::FRONT )
            {
                uint move_face = move % Face::_NUM_CUBE_FACES;
                uint move_type = move / Face::_NUM_CUBE_FACES;

                switch( move_face )
                {
                case Face::FRONT:
                    move = Face::getFrontOf( ( Face::TYPES )face );
                    break;
                case Face::BACK:
                    move = Face::getBackOf( ( Face::TYPES )face );
                    break;
                case Face::UP:
                    move = Face::getUpOf( ( Face::TYPES )face, ( Face::SPIN )spin );
                    break;
                case Face::DOWN:
                    move = Face::getDownOf( ( Face::TYPES )face, ( Face::SPIN )spin );
                    break;
                case Face::LEFT:
                    move = Face::getLeftOf( ( Face::TYPES )face, ( Face::SPIN )spin );
                    break;
                case Face::RIGHT:
                    move = Face::getRightOf( ( Face::TYPES )face, ( Face::SPIN )spin );
                    break;
                default:
                    break;
                }
                move += move_type * Face::_NUM_CUBE_FACES;
            }
            move += move_level_shift;
        }

        if( mirrored == 1 )
            std::reverse( moves.begin(), moves.end() );

        return moves;
    }
};
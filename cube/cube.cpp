#include "cube.hpp"

#include <stdexcept>
#include <cmath>
#include <fstream>

Cube::Cube()
    : size( 0 )
    , move_aux_arr( 0 ) {}

Cube::Cube( uint size ) 
{ 
    this->create( size ); 
}

Cube::Cube( const Cube & other )
{    
    this->create( other.size );
    other.copyTo( *this );
}

Cube::Cube( Cube && other )
{
    this->size = other.size;
    this->move_aux_arr = other.move_aux_arr;
    this->num_moves = other.num_moves;
    for( ushort i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        this->cube[ i ] = std::move( other.cube[ i ] );
}

Cube::~Cube()
{
    this->clear();
}

Cube & Cube::operator=( const Cube & other )
{
    if( this->size != 0 )
        this->clear();

    this->create( other.size );
    other.copyTo( *this );

    return *this;
}

Cube & Cube::operator=( Cube && other )
{
    if( this->size != 0 )
        this->clear();

    this->size = other.size;
    this->move_aux_arr = other.move_aux_arr;
    this->num_moves = other.num_moves;
    for( ushort i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        this->cube[ i ] = std::move( other.cube[ i ] );

    return *this;
}

void Cube::create( uint size )
{
    this->move_aux_arr = new char[ size ];
    for( ushort i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        this->cube[ i ].create( size, size );
    this->num_moves = Move::generate( size );
    this->size = size;
}

void Cube::clear()
{
    if( move_aux_arr )
    {
        delete[] move_aux_arr;
        move_aux_arr = 0;
    }

    for( ushort i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        this->cube[ i ].clear();

    this->size = 0;
}

void Cube::readFromFile( std::string&& f )
{
    std::string wrd;
    std::ifstream f_obj;
    f_obj.open( f.c_str() );

    if( !f_obj.is_open() )
        throw std::runtime_error( "Cube::readFromFile -> Couldn't read the cube from the specified file" );

    f_obj >> wrd;

    uint cube_size = std::stoi( wrd );

    this->create( cube_size );

    for( uint k = 0; k < Face::_NUM_CUBE_FACES; ++k )
    {
        f_obj >> wrd;
        Face::TYPES face;
        if( wrd == "Front" )
        {
            face = Face::FRONT;
        }
        else if( wrd == "Back" )
        {
            face = Face::BACK;
        }
        else if( wrd == "Left" )
        {
            face = Face::LEFT;
        }
        else if( wrd == "Right" )
        {
            face = Face::RIGHT;
        }
        else if( wrd == "Up" )
        {
            face = Face::UP;
        }
        else if( wrd == "Down" )
        {
            face = Face::DOWN;
        }
        for( uint i = 0; i < cube_size; ++i )
        {
            for( uint j = 0; j < cube_size; ++j )
            {
                f_obj >> wrd;
                this->cube[ face ].m[ i ][ j ] = wrd[ 0 ];
            }
        }
    }
}

void Cube::copyTo( Cube & other ) const
{
    if( other.size != this->size )
        throw std::invalid_argument( "Cube::copyTo -> Cubes are not of the same size" );

    for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        this->cube[ i ].copyTo( other.cube[ i ] );
}

void Cube::makeMove( uint move )
{
    if( move >= this->num_moves )
        throw std::invalid_argument( "Cube::makeMove -> move number exceeded the limit" );

    // 0 is the surface
    uint level = ( uint )std::floorf( ( float )( move ) / 
        ( float )( Face::_NUM_CUBE_FACES * Move::_NUM_MOVE_TYPES ) );

    // 90 degrees to the right (0), left (1) or 180 degrees (2)
    Move::TYPES move_type = ( Move::TYPES )( ( uint )( std::floorf( ( float )( move ) /
        ( float )( Face::_NUM_CUBE_FACES ) ) ) %
        Move::_NUM_MOVE_TYPES );

    // Front (0), back (1), up (2), down (3), left (4), right (5).
    Face::TYPES face = ( Face::TYPES )( move % Face::_NUM_CUBE_FACES );

    // Switch 4 segments
    switch( face )
    {
    case Face::TYPES::FRONT:
    {
        // [ 2 3 4 5 ]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateF90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            this->rotateF90i( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            this->rotateF180( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    case Face::TYPES::BACK:
    {
        // [ 2 3 4 5 ]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateB90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            // + 270 = - 90
            this->rotateB90( level );
            this->rotateB90( level );
            this->rotateB90( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            // + 180 = - 180
            this->rotateB90( level );
            this->rotateB90( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    case Face::TYPES::UP:
    {
        // [ 0 1 4 5 ]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateU90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            // + 270 = - 90
            this->rotateU90( level );
            this->rotateU90( level );
            this->rotateU90( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            // + 180 = - 180
            this->rotateU90( level );
            this->rotateU90( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    case Face::TYPES::DOWN:
    {
        // [ 0 1 4 5 ]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateD90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            // + 270 = - 90
            this->rotateD90( level );
            this->rotateD90( level );
            this->rotateD90( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            // + 180 = - 180
            this->rotateD90( level );
            this->rotateD90( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    case Face::TYPES::LEFT:
    {
        // [ 0 1 2 3 ]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateL90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            // + 270 = - 90
            this->rotateL90( level );
            this->rotateL90( level );
            this->rotateL90( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            // + 180 = - 180
            this->rotateL90( level );
            this->rotateL90( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    case Face::TYPES::RIGHT:
    {
        // [ 0 1 2 3 ]]
        switch( move_type )
        {
        case Move::TYPES::ROT90:
        {
            this->rotateR90( level );

            // Rotate the face if it is on the surface
            if( level == 0 )
                this->cube[ face ].rot90();

            break;
        }
        case Move::TYPES::ROT90I:
        {
            // + 270 = - 90
            this->rotateR90( level );
            this->rotateR90( level );
            this->rotateR90( level );

            if( level == 0 )
                this->cube[ face ].rot90i();

            break;
        }
        case Move::TYPES::ROT180:
        {
            // + 180 = - 180
            this->rotateR90( level );
            this->rotateR90( level );

            if( level == 0 )
                this->cube[ face ].rot180();

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

std::string Cube::getString()
{
    std::string * lines = new std::string[ this->size * 3 ];

    for( uint i = 0; i < this->size * 3; ++i )
    {
        lines[ i ].reserve( this->size * 4 + 3 );

        // In the "up" face
        if( i / this->size < 1 )
        {
            for( uint j = 0; j < this->size + 1; ++j )
            {
                lines[ i ] += " ";
            }

            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::UP ].m[ i ][ j ];
            }

            for( uint j = this->size; j < this->size * 4; ++j )
            {
                lines[ i ] += " ";
            }
        }
        // In the middle
        else if( i / this->size < 2 )
        {
            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::LEFT ].m[ i - this->size ][ j ];
            }
            lines[ i ] += " ";
            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::FRONT ].m[ i - this->size ][ j ];
            }
            lines[ i ] += " ";
            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::RIGHT ].m[ i - this->size ][ j ];
            }
            lines[ i ] += " ";
            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::BACK ].m[ i - this->size ][ j ];
            }
        }
        // In the "down" face
        else
        {
            for( uint j = 0; j < this->size + 1; ++j )
            {
                lines[ i ] += " ";
            }

            for( uint j = 0; j < this->size; ++j )
            {
                lines[ i ] += this->cube[ Face::DOWN ].m[ i - this->size * 2 ][ j ];
            }

            for( uint j = this->size; j < this->size * 4; ++j )
            {
                lines[ i ] += " ";
            }
        }
    }

    std::string str;
    // filled faces + empty spaces + \n's + spaces between middle faces and "up" "down" faces indentation
    str.reserve( this->size * 6 + this->size * 6 + this->size * 3 + this->size * 5 );

    for( uint i = 0; i < this->size * 3; i++ )
    {
        str += lines[ i ] += "\n";
    }
    str.pop_back();

    delete[] lines;
    return str;
}

void Cube::rotateF90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last line of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "left" face to "up"
        this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::LEFT ].m[ this->size - i - 1 ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "down" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::DOWN ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "right" face to "down"
        this->cube[ Face::TYPES::DOWN ].m[ level ][ i ] = 
            this->cube[ Face::TYPES::RIGHT ].m[ this->size - i - 1 ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "up" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ i ][ level ] = this->move_aux_arr[ i ];
    }
}

void Cube::rotateF90i( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last line of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "right" face to "up"
        this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::RIGHT ].m[ i ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "down" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ i ][ level ] =
            this->cube[ Face::TYPES::DOWN ].m[ level ][ this->size - i - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "left" face to "down"
        this->cube[ Face::TYPES::DOWN ].m[ level ][ i ] =
            this->cube[ Face::TYPES::LEFT ].m[ this->size - i - 1 ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "up" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ this->size - i - 1 ][ this->size - level - 1 ] =
            this->move_aux_arr[ i ];
    }
}

void Cube::rotateF180( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last line of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "down" face to "up"
        this->cube[ Face::TYPES::UP ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::DOWN ].m[ level ][ this->size - i - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "up" face to "down"
        this->cube[ Face::TYPES::DOWN ].m[ level ][ this->size - i - 1 ] =
            this->move_aux_arr[ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last column of the "left" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::LEFT ].m[ i ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "right" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::RIGHT ].m[ this->size - i - 1 ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "left" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ this->size - i - 1 ][ level ] =
            this->move_aux_arr[ i ];
    }
}

void Cube::rotateB90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the first line of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "right" face to "up"
        this->cube[ Face::TYPES::UP ].m[ level ][ i ] =
            this->cube[ Face::TYPES::RIGHT ].m[ i ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "down" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::DOWN ].m[ this->size - level - 1 ][ this->size - i - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "left" face to "down"
        this->cube[ Face::TYPES::DOWN ].m[ this->size - level - 1 ][ this->size - i - 1 ] =
            this->cube[ Face::TYPES::LEFT ].m[ this->size - i - 1 ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "up" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ this->size - i - 1 ][ level ] = this->move_aux_arr[ i ];
    }
}

void Cube::rotateU90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the first line of the "left" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::LEFT ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "front" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ level ][ i ] =
            this->cube[ Face::TYPES::FRONT ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "right" face to "front"
        this->cube[ Face::TYPES::FRONT ].m[ level ][ i ] =
            this->cube[ Face::TYPES::RIGHT ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "back" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ level ][ i ] = 
            this->cube[ Face::TYPES::BACK ].m[ level ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "left" face to "back"
        this->cube[ Face::TYPES::BACK ].m[ level ][ i ] = this->move_aux_arr[ i ];
    }
}

void Cube::rotateD90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last line of the "left" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::LEFT ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "back" face to "left"
        this->cube[ Face::TYPES::LEFT ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::BACK ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "right" face to "back"
        this->cube[ Face::TYPES::BACK ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::RIGHT ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last line of the "front" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ this->size - level - 1 ][ i ] =
            this->cube[ Face::TYPES::FRONT ].m[ this->size - level - 1 ][ i ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "left" face to "front"
        this->cube[ Face::TYPES::FRONT ].m[ this->size - level - 1 ][ i ] = this->move_aux_arr[ i ];
    }
}

void Cube::rotateL90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the first column of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ i ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "back" face to "up" (reversed)
        this->cube[ Face::TYPES::UP ].m[ i ][ level ] =
            this->cube[ Face::TYPES::BACK ].m[ this->size - i - 1 ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "down" face to "back" (reversed)
        this->cube[ Face::TYPES::BACK ].m[ this->size - i - 1 ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::DOWN ].m[ i ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first line of the "front" face to "down"
        this->cube[ Face::TYPES::DOWN ].m[ i ][ level ] =
            this->cube[ Face::TYPES::FRONT ].m[ i ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "up" face to "front"
        this->cube[ Face::TYPES::FRONT ].m[ i ][ level ] = this->move_aux_arr[ i ];
    }
}

void Cube::rotateR90( uint level )
{
    for( uint i = 0; i < this->size; ++i )
    {
        // Get the last column of the "up" face
        this->move_aux_arr[ i ] = this->cube[ Face::TYPES::UP ].m[ i ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "front" face to "up" (reversed)
        this->cube[ Face::TYPES::UP ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::FRONT ].m[ i ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "down" face to "front"
        this->cube[ Face::TYPES::FRONT ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::DOWN ].m[ i ][ this->size - level - 1 ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the first column of the "right" face to "down" (reversed)
        this->cube[ Face::TYPES::DOWN ].m[ i ][ this->size - level - 1 ] =
            this->cube[ Face::TYPES::RIGHT ].m[ this->size - i - 1 ][ level ];
    }

    for( uint i = 0; i < this->size; ++i )
    {
        // Set the last column of the "up" face to "right"
        this->cube[ Face::TYPES::RIGHT ].m[ this->size - i - 1 ][ level ] = this->move_aux_arr[ i ];
    }
}


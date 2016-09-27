#include "cube_prob.hpp"

#include <cmath>
#include <map>
#include <algorithm>

inline float gaussian( float x, float mu, float sigma )
{
    return ( float )std::exp( -( ( ( x - mu ) / ( sigma ) ) *
        ( ( x - mu ) / ( sigma ) ) ) / 2.0 );
}

CubeProblem::CubeProblem()
{}

CubeProblem::~CubeProblem()
{}

Cube CubeProblem::evalSolution( CubeSolution & sol )
{
    Cube c_tmp = this->cube;
    sol.fitness = 0;

    for( int & move : sol.moves )
    {
        if( move != CubeSolution::NAM )
        {
            // if the move is a smart move
            if( move >= ( int )this->cube.num_moves )
            {
                // Remove the offset
                uint s_m_idx = move - this->cube.num_moves;
                std::vector< uint > smart_moves = SmartMoves::getMove( s_m_idx );
                for( uint & s_m : smart_moves )
                    c_tmp.makeMove( s_m );
            }
            else
            {
                c_tmp.makeMove( ( uint )move );
            }
        }
    }

    // If the cube hasn't a size of even number (It has a center square)
    if( this->cube.size % 2 != 0 )
    {
        for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        {
            char face_color = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 ];

            for( uint j = 0; j < c_tmp.size; ++j )
                for( uint k = 0; k < c_tmp.size; ++k )
                    if( c_tmp.cube[ i ].m[ j ][ k ] != face_color )
                        sol.fitness += this->g_kernel[ j ][ k ];
        }
    }
    else
    {
        for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        {
            // Get the majority color of the 4 center squares (if it exists)
            char face_colors[ 4 ];
            face_colors[ 0 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 ];
            face_colors[ 1 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 + 1 ];
            face_colors[ 2 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 + 1 ][ c_tmp.size / 2 ];
            face_colors[ 3 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 + 1 ][ c_tmp.size / 2 + 1 ];
            uint counter[ 4 ] = { 0, 0, 0, 0 };
            for( uint j = 0; j < 3; ++j )
            {
                for( uint k = j + 1; k < 4; ++k )
                {
                    if( face_colors[ j ] == face_colors[ k ] )
                    {
                        counter[ j ]++;
                    }
                }
            }
            uint max_val = counter[ 0 ];
            uint max_val_idx = 0;
            bool draw = false;
            for( uint j = 1; j < 4; ++j )
            {
                if( counter[ j ] == max_val )
                {
                    draw = true;
                    break;
                }
                else if( counter[ j ] > max_val )
                {
                    max_val = counter[ j ];
                    max_val_idx = j;
                }
            }
            bool has_majority = false;
            char face_color;
            if( !draw && max_val != 0 )
            {
                has_majority = true;
                face_color = face_colors[ max_val_idx ];
            }

            if( has_majority )
            {
                for( uint j = 0; j < c_tmp.size; ++j )
                    for( uint k = 0; k < c_tmp.size; ++k )
                        if( c_tmp.cube[ i ].m[ j ][ k ] != face_color )
                            sol.fitness += this->g_kernel[ j ][ k ];
            }
            else // Penalizes everyone
            {
                for( uint j = 0; j < c_tmp.size; ++j )
                    for( uint k = 0; k < c_tmp.size; ++k )
                        sol.fitness += this->g_kernel[ j ][ k ];
            }
        }
    }

    return c_tmp;
}

Cube CubeProblem::evalSolution(
    std::vector< int > & moves,
    float & fitness,
    uint & num_moves,
    uint & num_diff_facelets,
    uint & freq
)
{
    Cube c_tmp = this->cube;
    fitness = 0;
    num_diff_facelets = 0;
    freq = 0;
    num_moves = 0;

    for( int & move : moves )
    {
        if( move != CubeSolution::NAM )
        {
            // if the move is a smart move
            if( move >= ( int )this->cube.num_moves )
            {
                // Remove the offset
                uint s_m_idx = move - this->cube.num_moves;
                std::vector< uint > smart_moves = SmartMoves::getMove( s_m_idx );
                for( uint & s_m : smart_moves )
                {
                    c_tmp.makeMove( s_m );
                    num_moves++;
                }
            }
            else
            {
                c_tmp.makeMove( ( uint )move );
                num_moves++;
            }
        }
    }

    // If the cube hasn't a size of even number (It has a center square)
    if( this->cube.size % 2 != 0 )
    {
        for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        {
            char face_color = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 ];

            for( uint j = 0; j < c_tmp.size; ++j )
                for( uint k = 0; k < c_tmp.size; ++k )
                    if( c_tmp.cube[ i ].m[ j ][ k ] != face_color )
                    {
                        fitness += this->g_kernel[ j ][ k ];
                        num_diff_facelets++;
                    }
        }
    }
    else
    {
        for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
        {
            // Get the majority color of the 4 center squares (if it exists)
            char face_colors[ 4 ];
            face_colors[ 0 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 ];
            face_colors[ 1 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 ][ c_tmp.size / 2 + 1 ];
            face_colors[ 2 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 + 1 ][ c_tmp.size / 2 ];
            face_colors[ 3 ] = c_tmp.cube[ i ].m[ c_tmp.size / 2 + 1 ][ c_tmp.size / 2 + 1 ];
            uint counter[ 4 ] = { 0, 0, 0, 0 };
            for( uint j = 0; j < 3; ++j )
            {
                for( uint k = j + 1; k < 4; ++k )
                {
                    if( face_colors[ j ] == face_colors[ k ] )
                    {
                        counter[ j ]++;
                    }
                }
            }
            uint max_val = counter[ 0 ];
            uint max_val_idx = 0;
            bool draw = false;
            for( uint j = 1; j < 4; ++j )
            {
                if( counter[ j ] == max_val )
                {
                    draw = true;
                    break;
                }
                else if( counter[ j ] > max_val )
                {
                    max_val = counter[ j ];
                    max_val_idx = j;
                }
            }
            bool has_majority = false;
            char face_color;
            if( !draw && max_val != 0 )
            {
                has_majority = true;
                face_color = face_colors[ max_val_idx ];
            }

            if( has_majority )
            {
                for( uint j = 0; j < c_tmp.size; ++j )
                    for( uint k = 0; k < c_tmp.size; ++k )
                        if( c_tmp.cube[ i ].m[ j ][ k ] != face_color )
                        {
                            fitness += this->g_kernel[ j ][ k ];
                            num_diff_facelets++;
                        }
            }
            else // Penalizes everyone
            {
                for( uint j = 0; j < c_tmp.size; ++j )
                    for( uint k = 0; k < c_tmp.size; ++k )
                    {
                        fitness += this->g_kernel[ j ][ k ];
                        num_diff_facelets++;
                    }
            }
        }
    }

    // Calculate distance metric
    std::vector< char > in_another_face;
    for( uint i = 0; i < Face::_NUM_CUBE_FACES; ++i )
    {
        std::map< char, uint >freq_map;
        for( uint j = 0; j < c_tmp.size; ++j )
            for( uint k = 0; k < c_tmp.size; ++k )
                freq_map[ c_tmp.cube[ i ].m[ j ][ k ] ]++;

        for( char & key : in_another_face )
            freq_map.erase( key );

        std::map< char, uint >::const_iterator f_max = std::max_element(
            freq_map.begin(),
            freq_map.end(),
            [ & ]( const std::pair< char, uint > & p1, const std::pair< char, uint > & p2 ) 
            {
                return p1.second < p2.second;
            }
        );

        in_another_face.push_back( f_max->first );

        freq += f_max->second ;
    }

    return c_tmp;
}

void CubeProblem::load( const std::string & file )
{
    this->cube.readFromFile( file );
    this->is_loaded = true;

    this->instance_name = file.substr( file.find_last_of( "/\\" ) + 1 );

    this->genModifiedGaussianKernel( this->cube.size / 2 );
}

void CubeProblem::genModifiedGaussianKernel( unsigned kernelRadius )
{
    float sigma = kernelRadius / 2.f;
    this->g_kernel = kernel_type( 2 * kernelRadius + 1, kernel_row( 2 * kernelRadius + 1 ) );
    for( std::size_t row = 0; row < this->g_kernel.size(); ++row )
    {
        for( std::size_t col = 0; col < this->g_kernel[ row ].size(); ++col )
        {
            float x = gaussian( ( float )row, ( float )kernelRadius, sigma )
                * gaussian( ( float )col, ( float )kernelRadius, sigma );
            this->g_kernel[ row ][ col ] = std::abs( x - 1.f ) * ( kernelRadius + 1 );
            this->g_kernel[ row ][ col ] *= this->g_kernel[ row ][ col ];
        }
    }

    if( this->cube.size % 2 == 0 )
    {
        this->g_kernel.erase( this->g_kernel.begin() + this->g_kernel.size() / 2 );
        for( kernel_row & row : this->g_kernel )
            row.erase( row.begin() + row.size() / 2 );
    }
}

#include <gtest/gtest.h>

#include "cube/cube.hpp"

class _Cube3 : public ::testing::Test
{
public:
    Cube c;

    void SetUp() { this->c.readFromFile( "in_test_3" ); }
    void TearDown() { this->c.clear(); }
};

TEST_F( _Cube3, ReadFromFile )
{
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 2 ], 'B' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 1 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 1 ][ 1 ], 'O' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 1 ][ 2 ], 'O' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 2 ], 'R' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 1 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 1 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 1 ][ 2 ], 'R' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 1 ], 'O' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 2 ], 'R' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 1 ], 'G' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 2 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 1 ], 'O' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 2 ], 'B' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 2 ], 'W' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 1 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 2 ], 'W' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 1 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 1 ][ 1 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 1 ][ 2 ], 'G' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 1 ], 'G' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 2 ], 'O' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 1 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 1 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 1 ][ 2 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 2 ], 'G' );
}

TEST_F( _Cube3, RotF90 )
{
    // F
    c.makeMove( 0 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 1 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 0 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 2 ], 'W' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 2 ], 'G' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 2 ], 'O' );
}

TEST_F( _Cube3, RotF90i )
{
    // Fi
    c.makeMove( 6 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 2 ], 'G' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 0 ], 'W' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 1 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 2 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 2 ], 'R' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 2 ], 'Y' );
}

TEST_F( _Cube3, RotF180 )
{
    // F2
    c.makeMove( 12 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 1 ], 'G' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 0 ], 'R' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 2 ], 'G' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 2 ], 'W' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 2 ], 'R' );
}

TEST_F( _Cube3, RotB90 )
{
    // F
    c.makeMove( 1 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 2 ], 'G' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 2 ], 'R' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 2 ], 'O' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 1 ], 'G' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 2 ], 'B' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 0 ], 'W' );
}

TEST_F( _Cube3, RotB90i )
{
    // Bi
    c.makeMove( 7 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 1 ], 'G' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 2 ], 'B' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 2 ], 'W' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 2 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 2 ], 'B' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 0 ], 'G' );
}

TEST_F( _Cube3, RotB180 )
{
    // B2
    c.makeMove( 13 );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 2 ], 'O' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 2 ], 'B' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 1 ][ 2 ], 'G' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 2 ], 'B' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 1 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 1 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 0 ], 'B' );
}

TEST_F( _Cube3, RotU90 )
{
    // U
    c.makeMove( 2 );

    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 1 ], 'O' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 2 ], 'B' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 0 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 1 ], 'O' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 0 ][ 2 ], 'B' );
}

TEST_F( _Cube3, RotD90 )
{
    // D
    c.makeMove( 3 );

    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 0 ], 'B' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 1 ], 'B' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 2 ], 'R' );

    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::RIGHT ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 1 ], 'R' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 2 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 0 ], 'O' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 1 ], 'W' );
    EXPECT_EQ( c.cube[ Face::LEFT ].m[ 2 ][ 2 ], 'Y' );
}

TEST_F( _Cube3, RotL90 )
{
    // L
    c.makeMove( 4 );

    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 0 ][ 0 ], 'W' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 1 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::FRONT ].m[ 2 ][ 0 ], 'Y' );

    EXPECT_EQ( c.cube[ Face::UP ].m[ 0 ][ 0 ], 'Y' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 1 ][ 0 ], 'R' );
    EXPECT_EQ( c.cube[ Face::UP ].m[ 2 ][ 0 ], 'R' );

    EXPECT_EQ( c.cube[ Face::BACK ].m[ 0 ][ 2 ], 'O' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 1 ][ 2 ], 'O' );
    EXPECT_EQ( c.cube[ Face::BACK ].m[ 2 ][ 2 ], 'W' );

    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 0 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 1 ][ 0 ], 'G' );
    EXPECT_EQ( c.cube[ Face::DOWN ].m[ 2 ][ 0 ], 'G' );
}

TEST_F( _Cube3, CopyTo )
{ 
    Cube c2( c.size );

    EXPECT_NO_THROW( c.copyTo( c2 ) );

    for( ushort i = 0; i < c.size; ++i )
        for( ushort j = 0; j < c.size; ++j )
            for( ushort k = 0; k < Face::_NUM_CUBE_FACES; ++k )
                EXPECT_EQ( c.cube[ k ].m[ i ][ j ], c2.cube[ k ].m[ i ][ j ] );
}

TEST_F( _Cube3, Assign )
{
    Cube c2 = c;

    for( ushort i = 0; i < c.size; ++i )
        for( ushort j = 0; j < c.size; ++j )
            for( ushort k = 0; k < Face::_NUM_CUBE_FACES; ++k )
                EXPECT_EQ( c.cube[ k ].m[ i ][ j ], c2.cube[ k ].m[ i ][ j ] );

    c.clear();

    for( ushort i = 0; i < c2.size; ++i )
        for( ushort j = 0; j < c2.size; ++j )
            for( ushort k = 0; k < Face::_NUM_CUBE_FACES; ++k )
                EXPECT_NO_THROW( c2.cube[ k ].m[ i ][ j ] = i + j + k );
}
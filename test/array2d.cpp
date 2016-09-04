#include <gtest/gtest.h>

#include "cube/matrix.hpp"

TEST( _Array2D, CreateAndDelete )
{
    Array2D< uint > v;
    v.create( 3, 5 );

    EXPECT_TRUE( v.m );
    EXPECT_EQ( 5, v.cols );
    EXPECT_EQ( 3, v.rows );

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            EXPECT_NO_THROW( v.m[ i ][ j ] = i + j );


    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            EXPECT_EQ( v.m[ i ][ j ], i + j );

    EXPECT_NO_THROW( v.clear() );
}

TEST( _Array2D, CopyTo )
{
    Array2D< uint > v, v2;
    v.create( 3, 3 );

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            v.m[ i ][ j ] = i + j;

    v2.create( v.rows, v.cols );
    v.copyTo( v2 );

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            EXPECT_EQ( v.m[ i ][ j ], i + j );
}

TEST( _Array2D, Assign )
{
    Array2D< uint > v, v2;
    v.create( 3, 3 );

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            v.m[ i ][ j ] = i + j;

    v2 = v;

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            EXPECT_EQ( v.m[ i ][ j ], v2.m[ i ][ j ] );

    v.clear();

    for( uint i = 0; i < v2.rows; ++i )
        for( uint j = 0; j < v2.cols; ++j )
            EXPECT_NO_THROW( v2.m[ i ][ j ] = i + j );
}

TEST( _Array2D, Rot90 )
{
    Array2D< uint > v;
    v.create( 3, 3 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 1 ][ 0 ] = 3;
    v.m[ 1 ][ 1 ] = 4;
    v.m[ 1 ][ 2 ] = 5;
    v.m[ 2 ][ 0 ] = 6;
    v.m[ 2 ][ 1 ] = 7;
    v.m[ 2 ][ 2 ] = 8;

    v.rot90();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 6 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 3 );
    EXPECT_EQ( v.m[ 0 ][ 2 ], 0 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 7 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 4 );
    EXPECT_EQ( v.m[ 1 ][ 2 ], 1 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 8 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 5 );
    EXPECT_EQ( v.m[ 2 ][ 2 ], 2 );

    v.clear();
    v.create( 2, 3 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 1 ][ 0 ] = 3;
    v.m[ 1 ][ 1 ] = 4;
    v.m[ 1 ][ 2 ] = 5;

    v.rot90();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 3 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 0 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 4 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 1 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 5 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 2 );
}

TEST( _Array2D, Rot90i )
{
    Array2D< uint > v;
    v.create( 3, 3 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 1 ][ 0 ] = 3;
    v.m[ 1 ][ 1 ] = 4;
    v.m[ 1 ][ 2 ] = 5;
    v.m[ 2 ][ 0 ] = 6;
    v.m[ 2 ][ 1 ] = 7;
    v.m[ 2 ][ 2 ] = 8;

    v.rot90i();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 2 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 5 );
    EXPECT_EQ( v.m[ 0 ][ 2 ], 8 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 1 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 4 );
    EXPECT_EQ( v.m[ 1 ][ 2 ], 7 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 0 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 3 );
    EXPECT_EQ( v.m[ 2 ][ 2 ], 6 );

    v.clear();
    v.create( 2, 3 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 1 ][ 0 ] = 3;
    v.m[ 1 ][ 1 ] = 4;
    v.m[ 1 ][ 2 ] = 5;

    v.rot90i();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 2 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 5 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 1 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 4 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 0 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 3 );
}

TEST( _Array2D, Rot180 )
{
    Array2D< uint > v;
    v.create( 3, 3 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 1 ][ 0 ] = 3;
    v.m[ 1 ][ 1 ] = 4;
    v.m[ 1 ][ 2 ] = 5;
    v.m[ 2 ][ 0 ] = 6;
    v.m[ 2 ][ 1 ] = 7;
    v.m[ 2 ][ 2 ] = 8;

    v.rot180();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 8 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 7 );
    EXPECT_EQ( v.m[ 0 ][ 2 ], 6 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 5 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 4 );
    EXPECT_EQ( v.m[ 1 ][ 2 ], 3 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 2 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 1 );
    EXPECT_EQ( v.m[ 2 ][ 2 ], 0 );

    v.clear();
    v.create( 4, 4 );

    v.m[ 0 ][ 0 ] = 0;
    v.m[ 0 ][ 1 ] = 1;
    v.m[ 0 ][ 2 ] = 2;
    v.m[ 0 ][ 3 ] = 3;
    v.m[ 1 ][ 0 ] = 4;
    v.m[ 1 ][ 1 ] = 5;
    v.m[ 1 ][ 2 ] = 6;
    v.m[ 1 ][ 3 ] = 7;
    v.m[ 2 ][ 0 ] = 8;
    v.m[ 2 ][ 1 ] = 9;
    v.m[ 2 ][ 2 ] = 10;
    v.m[ 2 ][ 3 ] = 11;
    v.m[ 3 ][ 0 ] = 12;
    v.m[ 3 ][ 1 ] = 13;
    v.m[ 3 ][ 2 ] = 14;
    v.m[ 3 ][ 3 ] = 15;

    v.rot180();

    EXPECT_EQ( v.m[ 0 ][ 0 ], 15 );
    EXPECT_EQ( v.m[ 0 ][ 1 ], 14 );
    EXPECT_EQ( v.m[ 0 ][ 2 ], 13 );
    EXPECT_EQ( v.m[ 0 ][ 3 ], 12 );
    EXPECT_EQ( v.m[ 1 ][ 0 ], 11 );
    EXPECT_EQ( v.m[ 1 ][ 1 ], 10 );
    EXPECT_EQ( v.m[ 1 ][ 2 ], 9 );
    EXPECT_EQ( v.m[ 1 ][ 3 ], 8 );
    EXPECT_EQ( v.m[ 2 ][ 0 ], 7 );
    EXPECT_EQ( v.m[ 2 ][ 1 ], 6 );
    EXPECT_EQ( v.m[ 2 ][ 2 ], 5 );
    EXPECT_EQ( v.m[ 2 ][ 3 ], 4 );
    EXPECT_EQ( v.m[ 3 ][ 0 ], 3 );
    EXPECT_EQ( v.m[ 3 ][ 1 ], 2 );
    EXPECT_EQ( v.m[ 3 ][ 2 ], 1 );
    EXPECT_EQ( v.m[ 3 ][ 3 ], 0 );
}
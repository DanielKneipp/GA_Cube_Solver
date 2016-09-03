#include <iostream>

#include <gtest/gtest.h>

#include "cube/cube.hpp"
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
            v.m[ i ][ j ] = i + j ;

    v2.create( v.rows, v.cols );
    v.copyTo( v2 );

    for( uint i = 0; i < v.rows; ++i )
        for( uint j = 0; j < v.cols; ++j )
            EXPECT_EQ( v.m[ i ][ j ], i + j );
}

TEST( _Array2D, Clone )
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

TEST( _Cube, ReadFromFile )
{
    Cube c;
    EXPECT_NO_THROW( c.readFromFile( "inTest" ));

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

TEST( _Cube, Rot3F90 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3F90i )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3F180 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3B90 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3B90i )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3B180 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3U90 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3D90 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, Rot3L90 )
{
    Cube c;
    c.readFromFile( "inTest" );
    //std::cout << c.getString() << "\n" << std::endl;

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

    //std::cout << c.getString() << std::endl;
}

TEST( _Cube, CopyTo )
{
    Cube c;
    c.readFromFile( "inTest" );

    Cube c2( c.size );

    EXPECT_NO_THROW( c.copyTo( c2 ) );

    for( ushort i = 0; i < c.size; ++i )
        for( ushort j = 0; j < c.size; ++j )
            for( ushort k = 0; k < Face::_NUM_CUBE_FACES; ++k )
                EXPECT_EQ( c.cube[ k ].m[ i ][ j ], c2.cube[ k ].m[ i ][ j ] );
}

TEST( _Cube, Clone )
{
    Cube c;
    c.readFromFile( "inTest" );

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

int main( int argc, char **argv ) 
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>

#include "cube/cube.hpp"

class _Cube4 : public ::testing::Test
{
public:
    Cube c;

    void SetUp() { this->c.readFromFile( "in_test_4" ); }
    void TearDown() { this->c.clear(); }
};

TEST_F( _Cube4, Solve )
{
    c.makeMove( 30 ); // 2F2
    c.makeMove( 20 ); // 2U
    c.makeMove( 28 ); // 2L'
    c.makeMove( 3 );  // D
    c.makeMove( 11 ); // R'

    EXPECT_TRUE( c.isSolved() );
}
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "cube_prob.hpp"

enum ERROR
{
    ARGS = -1
};

void printHelp()
{
    std::cout << "Usage: test_solution <instance> <number-format-solution>";
}

int main( int argc, char ** argv )
{
    if( argc < 3 )
    {
        printHelp();
        return ERROR::ARGS;
    }

    CubeProblem prob; prob.load( argv[1] );

    std::cout << "\n\nInput cube:\n\n" << prob.cube.getString() << "\n" << std::endl;

    std::stringstream sol_str( argv[2] );
    std::string wrd;
    std::vector< int > moves;
    moves.reserve( 300 );

    while( sol_str >> wrd )
        moves.push_back(std::stoi(wrd));
   
    float fitness; uint num_diff_facelets; uint freq; uint num_moves;
    Cube c = prob.evalSolution( moves, fitness, num_moves, num_diff_facelets, freq );
    float dist = ( float )freq / ( float )( prob.cube.size * prob.cube.size );

    std::cout << "\nResult:\n\n" << c.getString() << "\n" << std::endl;
    std::cout << "Fitness: " << fitness << std::endl;
    std::cout << "Number of movements: " << num_moves << std::endl;
    std::cout << "Distance measure: " << freq << "/" << prob.cube.size * prob.cube.size << " = " << dist << std::endl;
    std::cout << "Number of different facelets: " << num_diff_facelets << "\n" << std::endl;
}
#include <iostream>

#include "ga.hpp"

void printHelp()
{
    std::cout << "Usage: cube_ga_solver "
        << "<instance> <config-file> <output-folder> [<num-of-execs>]" << std::endl;
}

enum ErrorTypes
{
    NUM_ARGS = -1,
    EXCEPTION = -2
};

int main( int argc, char ** argv )
{
    if( argc < 4 )
    {
        printHelp();
        return ErrorTypes::NUM_ARGS;
    }

    std::ofstream coutFile;

    unsigned num_execs = 1;
    if( argc >= 5 )
    {
        try
        {
            num_execs = std::stoi( argv[ 4 ] );
        }
        catch( std::exception& e )
        {
            std::cerr << e.what() << std::endl;
            return ErrorTypes::EXCEPTION;
        }
    }

    std::cout << "\n\n=================================" << std::endl
        << "-------- CUBEGA INITIATED --------" << std::endl;

    CubeGA cube_solver;
    cube_solver.problem.load( argv[ 1 ] );
    cube_solver.config.load( argv[ 2 ] );
    cube_solver.setOutputFolder( argv[ 3 ] );

    std::cout << "Instance: " << cube_solver.problem.instance_name << std::endl;
    std::cout << cube_solver.config.toString() << std::endl;

    for( unsigned i = 1; i <= num_execs; i++ )
    {
        std::cout << "\n==================================" << std::endl
            << "------- EXECUTION " << i << " STARTED ------" << std::endl;

        try
        {
            cube_solver.run();

            std::cout << "Total execution time: " 
                << std::chrono::duration_cast< std::chrono::milliseconds >
                ( cube_solver.execution_time ).count()
                << " milliseconds" << std::endl;
        }
        catch( std::exception& e )
        {
            std::cerr << e.what() << std::endl;
            return ErrorTypes::EXCEPTION;
        }

        std::cout << "-------  EXECUTION " << i << " DONE  -------" << std::endl
            << "==================================" << std::endl;
    }

    std::cout << "\n---------  CUBEGA DONE  ----------" << std::endl
        << "==================================" << std::endl;

    return 0;
}
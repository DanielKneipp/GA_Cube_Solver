#include "ga.hpp"

#include <stdexcept>

#define castMicro( t ) std::chrono::duration_cast< std::chrono::microseconds >( t )
#define getTimeNow() std::chrono::steady_clock::now()

typedef std::chrono::steady_clock::time_point TimePoint;
typedef std::vector< CubeSolution > CubeSols;

inline void calcAllFits( CubeSols & sols, CubeProblem & prob )
{
    for( CubeSolution & sol : sols )
        prob.evalSolution( sol );
}

CubeGA::CubeGA() {}

CubeGA::~CubeGA() {}

void CubeGA::run()
{
    // Verifies if the configuration was loaded
    if( !this->config.is_loaded )
        throw std::exception( "Configuration wasn't loaded" );

    // Create output file name with path
    this->logger.defineOutputFileName( this->config, this->problem );

    // TODO: Generate individuals
    CubeSols sols( this->config.NUM_INDIV );

    // Calculate Fitness
    calcAllFits( sols, this->problem );

    TimePoint start_t = getTimeNow();
    // Starting evolutionary process

        // TODO: Select Individuals (with or without elitism)

        // TODO: Crossover or mutate the individuals

        // TODO: Calculate Fitness again

        // TODO: Call logger to save statistics

    TimePoint end_t = getTimeNow();
    this->executionTime = castMicro( end_t - start_t );

    // Plot the result
    this->logger.plotStoredData();
}

void CubeGA::setOutputFolder( std::string & path )
{
    this->logger.setOutputFolder( path );
}

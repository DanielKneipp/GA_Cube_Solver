#include "ga.hpp"

#include <stdexcept>

#include "utils.hpp"

#define castMicro( t ) std::chrono::duration_cast< std::chrono::microseconds >( t )
#define getTimeNow() std::chrono::steady_clock::now()

typedef std::chrono::steady_clock::time_point TimePoint;

inline void calcAllFits( CubeSols & sols, CubeProblem & prob )
{
    for( CubeSolution & sol : sols )
        prob.evalSolution( sol );
}

CubeGA::CubeGA() {}

CubeGA::~CubeGA() {}

CubeSols CubeGA::genRandSols( )
{
    CubeSols sols( this->config.NUM_INDIV );
    uint num_moves = Move::generate( this->problem.cube.size );

    for( uint i = 0; i < this->config.NUM_INDIV; ++i )
        for( uint j = 0; j < CubeSolution::NUM_MOVES; ++j )
            sols[ i ].moves[ j ] = genIntRandNumber( ( uint )0, num_moves - 1 );

    return sols;
}

CubeSols CubeGA::moveFlipMutation( CubeSols & sols, float prob_m, float prob_gene )
{
    return CubeSols();
}

CubeSols CubeGA::cutPointCrossover( CubeSols & sols, float prob, uint n_cuts )
{
    return CubeSols();
}

CubeSols CubeGA::tournament( CubeSols & sols, uint size, uint num_sols_to_select )
{
    CubeSols chosen;
    chosen.reserve( num_sols_to_select );

    for( uint i = 0; i < num_sols_to_select; ++i )
    {
        uint p = genIntRandNumber< uint >( 0, ( uint )sols.size() );
        CubeSolution the_one = sols[ p ];
        for( uint j = 0; j < size; ++j )
        {
            p = genIntRandNumber< uint >( 0, ( uint )sols.size() );
            if( sols[ p ] < the_one )
                the_one = sols[ p ];
        }
        chosen.push_back( the_one );
    }
    return CubeSols();
}

CubeSols CubeGA::getBest( CubeSols & sols, uint num_of_best )
{
    return CubeSols();
}

void CubeGA::run()
{
    // Verifies if the configuration was loaded
    if( !this->config.is_loaded )
        throw std::exception( "Configuration wasn't loaded" );

    // Create output file name with path
    this->logger.defineOutputFileName( this->config, this->problem );

    // Generate individuals
    CubeSols sols = this->genRandSols();

    // Calculate Fitness
    calcAllFits( sols, this->problem );

    TimePoint start_t = getTimeNow();

    // Starting evolutionary process
    for( uint i = 0; i < this->config.NUM_GENS; ++i )
    {
        //TODO: Select the 10% best individuals (elites)

        //TODO: Select Individuals (with or without elitism)

        //TODO: Crossover or mutate the individuals

        //TODO: Calculate Fitness of the children and mutated

        //TODO: Join the elites to the mutated and children

        //TODO: Call logger to save statistics
    }

    TimePoint end_t = getTimeNow();
    this->executionTime = castMicro( end_t - start_t );

    // Plot the result
    this->logger.plotStoredData();
}

void CubeGA::setOutputFolder( std::string & path )
{
    this->logger.setOutputFolder( path );
}

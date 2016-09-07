#include "ga.hpp"

#include <stdexcept>
#include <algorithm>

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
    CubeSols mutated;
    mutated.reserve( sols.size() );

    for( CubeSolution & sol : sols )
    {
        float p = genRealRandNumber< float >( 0, 1 );
        if( p < prob_m )
        {
            CubeSolution m = sol;
            bool changed = false;
            for( uint i = 0; i < CubeSolution::NUM_MOVES; ++i )
            {
                p = genRealRandNumber< float >( 0, 1 );
                if( p < prob_gene )
                {
                    int move = genIntRandNumber( 0, Move::NUM_MOVE_TYPES - 1 );
                    m.moves[ i ] = move;
                    changed = true;
                }
            }
            if( changed ) this->problem.evalSolution( m );
            mutated.push_back( m );
        }
    }

    return mutated;
}

CubeSols CubeGA::cutPointCrossover( 
    CubeSols & sols, 
    float prob, 
    uint & num_better_children,
    uint & num_worse_children,
    uint n_cuts
)
{
    CubeSols children;
    children.reserve( sols.size() );
    uint cutpoint_range_step = ( uint )sols.size() / n_cuts;

    std::vector< std::size_t > cut_points( n_cuts );

    for( std::size_t i = 0; i < sols.size(); i = i + 2 )
    {
        float p = genRealRandNumber< float >( 0, 1 );

        if( p < prob )
        {
            // Generating the cut points
            std::size_t j = 0;
            // The last range has to include the last position
            for(; j < n_cuts - 1 ; ++j )
            {
                cut_points[ j ] = genIntRandNumber< std::size_t >(
                    j * cutpoint_range_step,
                    ( j + 1 ) * cutpoint_range_step - 1
                );
            }
            cut_points[ j ] = genIntRandNumber< std::size_t >(
                j * cutpoint_range_step,
                ( std::size_t )CubeSolution::NUM_MOVES
            );
            std::sort( cut_points.begin(), cut_points.end() );
            
            // Do the crossover
            j = 0;
            CubeSolution new_children[ 2 ];
            for( uint k = 0; k < CubeSolution::NUM_MOVES; ++k )
            {

                if( j < n_cuts && k == cut_points[ j ] )
                    ++j;

                if( j % 2 == 0 )
                {
                    new_children[ 0 ].moves[ k ] = sols[ i ].moves[ k ];
                    new_children[ 1 ].moves[ k ] = sols[ i + 1 ].moves[ k ];
                }
                else
                {
                    new_children[ 1 ].moves[ k ] = sols[ i ].moves[ k ];
                    new_children[ 0 ].moves[ k ] = sols[ i + 1 ].moves[ k ];
                }
            }
            // Calculate the children fitness
            this->problem.evalSolution( new_children[ 0 ] );
            this->problem.evalSolution( new_children[ 1 ] );

            // Add children
            children.push_back( new_children[ 0 ] );
            children.push_back( new_children[ 1 ] );

            // Get some statistics
            float paren_mean_fit = ( sols[ i ].fitness + sols[ i + 1 ].fitness ) / 2;
            // < = better
            if( new_children[ 0 ].fitness < paren_mean_fit ) num_better_children++; 
            else num_worse_children++;
            if( new_children[ 1 ].fitness < paren_mean_fit ) num_better_children++;
            else num_worse_children++;
        }
    }
    
    return children;
}

CubeSols CubeGA::smartMovesMutation( CubeSols & sols, float prob_m )
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

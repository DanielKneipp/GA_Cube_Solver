#include "ga.hpp"

#include <stdexcept>
#include <algorithm>

#include "utils.hpp"

#define _FLIP_MUT_GENS_PERC 0.3f
#define _FLIP_MUT_GEN_PROB 0.15f

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

CubeSols CubeGA::genRandSols( uint num_sols )
{
    CubeSols sols( num_sols );

    for( uint i = 0; i < num_sols; ++i )
        for( uint j = 0; j < CubeSolution::NUM_MOVES; ++j )
        {
            sols[ i ].moves[ j ] = genIntRandNumber< uint >( 
                ( uint )0, 
                this->problem.cube.num_moves - 1 
            );
        }

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
                    int move = genIntRandNumber< int >( 
                        CubeSolution::NAM, 
                        this->problem.cube.num_moves - 1 
                    );
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

            // new_children[ 0 ].moveNAMtoTheEnd();
            // new_children[ 1 ].moveNAMtoTheEnd();

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

void CubeGA::runGenWithFlipMut( 
    CubeSols & sols,
    uint & num_better_children,
    uint & num_worse_children
)
{
    // Select n best individuals (elites)
    CubeSols elites = getNSols(
        sols,
        this->config.NUM_ELITES,
        []( const CubeSolution & s1, const CubeSolution & s2 ) -> bool
        {
            return s1 < s2;
        }
    );

    // Select n individuals, with n = this->config.NUM_INDIV - this->config.NUM_ELITES
    CubeSols selected = tournament(
        sols,
        this->config.TOURN_SIZE,
        this->config.NUM_ELITES - ( uint )elites.size()
    );

    // Crossover or mutate (using flip) the individuals
    CubeSols children = cutPointCrossover(
        selected,
        this->config.P_CROSS,
        num_better_children,
        num_worse_children
    );

    CubeSols mutated = moveFlipMutation( sols, this->config.P_MUT, _FLIP_MUT_GEN_PROB );

    // Join the elites to the mutated and children
    sols.clear();
    sols.reserve( elites.size() + mutated.size() + children.size() );
    sols.insert( sols.end(), elites.begin(), elites.end() );
    sols.insert( sols.end(), mutated.begin(), mutated.end() );
    sols.insert( sols.end(), children.begin(), children.end() );
}

void CubeGA::runGenWithSmartMut( 
    CubeSols & sols,
    uint & num_better_children,
    uint & num_worse_children
)
{
    // Select n best individuals (elites)
    CubeSols elites = getNSols(
        sols,
        this->config.NUM_ELITES,
        []( const CubeSolution & s1, const CubeSolution & s2 ) -> bool
        {
            return s1 < s2;
        }
    );

    // Select n individuals, with n = this->config.NUM_INDIV - this->config.NUM_ELITES
    CubeSols selected = tournament(
        sols,
        this->config.TOURN_SIZE,
        this->config.NUM_ELITES - ( uint )elites.size()
    );

    // Crossover or mutate (using flip) the individuals
    CubeSols children = cutPointCrossover(
        selected,
        this->config.P_CROSS,
        num_better_children,
        num_worse_children
    );

    CubeSols mutated = smartMovesMutation( sols, this->config.P_MUT );

    // Join the elites to the mutated and children
    sols.clear();
    sols.reserve( elites.size() + mutated.size() + children.size() );
    sols.insert( sols.end(), elites.begin(), elites.end() );
    sols.insert( sols.end(), mutated.begin(), mutated.end() );
    sols.insert( sols.end(), children.begin(), children.end() );
}

void CubeGA::run()
{
    // Verifies if the configuration was loaded
    if( !this->config.is_loaded )
        throw std::exception( "Configuration wasn't loaded" );

    // Create output file name with path
    this->logger.defineOutputFileName( this->config, this->problem );

    // Generate individuals
    CubeSols sols = this->genRandSols( this->config.NUM_INDIV );

    // Calculate Fitness
    calcAllFits( sols, this->problem );

    TimePoint start_t = getTimeNow();

    // Starting evolutionary process
    if( this->config.USE_ELIT )
    {
        uint i = 0,
            num_better_children = 0,
            num_worse_children = 0;
        for( ; i < this->config.NUM_GENS * _FLIP_MUT_GENS_PERC; ++i )
        {
            this->runGenWithFlipMut(
                sols,
                num_better_children,
                num_worse_children
            );

            // Call logger to save statistics
            this->logger.storeStats( sols, num_better_children, num_worse_children );
        }
        for( ; i < this->config.NUM_GENS; ++i )
        {
            this->runGenWithSmartMut(
                sols,
                num_better_children,
                num_worse_children
            );

            // Call logger to save statistics
            this->logger.storeStats( sols, num_better_children, num_worse_children );
        }
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

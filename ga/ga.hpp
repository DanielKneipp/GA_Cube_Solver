#pragma once

#include <chrono>
#include <string>
#include <fstream>

#include "cube_sol.hpp"
#include "ga_conf.hpp"
#include "logger.hpp"

typedef std::vector< CubeSolution > CubeSols;

class CubeGA
{
public:
    std::chrono::microseconds execution_time;
    CubeGAConfig config;
    CubeSolution best_sol;
    CubeProblem problem;
    Logger logger;

    CubeGA();
    ~CubeGA();
    void run();
    void setOutputFolder( const std::string & path );

private:
    // ********************************************************************************
    /// <summary>
    /// Generate individuals in a randomly way. Note that the 
    /// <see cref="CubeSolution::NAM"/> is included in the move range.
    /// </summary>
    /// <param name="num_sols">Number of solutions (Population size)</param>
    /// <returns>Generated individuals</returns>
    /// <created>Daniel Kneipp,9/7/2016</created>
    /// <changed>Daniel Kneipp,9/7/2016</changed>
    // ********************************************************************************
    CubeSols genRandSols( uint num_sols );
    // ********************************************************************************
    /// <summary>
    /// Changes a movement randomly according to the probability <paramref name="prob_m"/>. 
    /// A individual has a probability <paramref name="prob_m"/> of be chosen.
    /// </summary>
    /// <param name="sols"> Individuals (solutions) </param>
    /// <param name="prob_m"> Probability of a individual be chosen </param>
    /// <param name="prob_gene"> Probability of a gene be chosen to be mutated </param>
    /// <returns> Mutated individuals with their fitness evaluated </returns>
    /// <created>Daniel Kneipp,9/6/2016</created>
    /// <changed>Daniel Kneipp,9/6/2016</changed>
    // ********************************************************************************
    CubeSols moveFlipMutation( CubeSols & sols, float prob_m, float prob_gene );
    // ********************************************************************************
    /// <summary>
    /// It apply N-cutpoint crossover operator on the individuals. It combines the 
    /// parent genes even if it are composed with <see cref="CubeSolution::NAM"/>.
    /// </summary>
    /// <param name="sols">Individuals (Parents)</param>
    /// <param name="prob">Probability of two Individuals be chosen to generate
    /// two children</param>
    /// <param name="num_better_children">Output parameter that specifies
    /// the number of children that are better than his parents</param>
    /// <param name="num_worse_children">Output parameter that specifies
    /// the number of children that are worse than their parents </param>
    /// <param name="n_cuts">Number of cut points</param>
    /// <returns>Children with their fitness calculated</returns>
    /// <remarks>
    /// The number of parents (<paramref name="sols"/>) must be even
    /// and should be shuffled because the parents will be choose pairwise
    /// sequentially.
    /// </remarks>
    /// <created>Daniel Kneipp,9/6/2016</created>
    /// <changed>Daniel Kneipp,9/6/2016</changed>
    // ********************************************************************************
    CubeSols cutPointCrossover( 
        CubeSols & sols, 
        float prob,
        uint & num_better_children,
        uint & num_worse_children,
        uint n_cuts = 1 
    );
    // ********************************************************************************
    /// <summary>
    /// Mutated the individual using a set of predefined movements that tends to don't 
    /// impact critically the individual fitness. It is good to be used on exploitation
    /// phase.
    /// </summary>
    /// <param name="sols"> Individuals </param>
    /// <param name="prob_m"> Mutation probability </param>
    /// <returns> Mutated individuals </returns>
    /// <created>Daniel Kneipp,9/6/2016</created>
    /// <changed>Daniel Kneipp,9/6/2016</changed>
    // ********************************************************************************
    CubeSols smartMovesMutation( CubeSols & sols, float prob_m );
    CubeSols tournament( CubeSols & sols, uint size, uint num_sols_to_select );
};


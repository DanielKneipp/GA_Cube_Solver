#pragma once

#include <string>

typedef unsigned int uint;

struct CubeGAConfig
{
    /// Number of individuals
    uint NUM_INDIV;
    /// Number of generations
    uint NUM_GENS;
    /// Crossover probability
    float P_CROSS;
    /// Mutation probability
    float P_MUT;
    /// Tournament size 
    uint TOURN_SIZE;
    /// Specifies if it should use elitism 
    bool USE_ELIT;
    /// Number of elites
    uint NUM_ELITES;
    /// Number of cut points
    uint N_CUT_POINTS;
    /// Probability of the genes being mutated by the flip operator
    float FLIP_MUT_GEN_PROB;
    /// After this number of generations, smart moves 
    /// will be used as mutation operator
    uint NUM_GENS_WITH_FLIP;
    /// Specifies the probability of a gene be <see cref="CubeSolution::NAM"/>
    /// on the initial population
    float INIT_POP_PROB_GENE_BE_NAM;
    /// Configuration name
    std::string CONFIG_NAME;
    bool is_loaded;

    CubeGAConfig();
    void load( const std::string& file_name );
    std::string toString() const;
};
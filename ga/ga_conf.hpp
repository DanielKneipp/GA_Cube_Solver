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
    /// Configuration name
    std::string CONFIG_NAME;
    bool is_loaded;

    CubeGAConfig();
    void load( const std::string& file_name );
    std::string toString() const;
};
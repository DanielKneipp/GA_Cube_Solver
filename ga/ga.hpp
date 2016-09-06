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
    std::chrono::microseconds executionTime;
    CubeGAConfig config;
    CubeSolution best_sol;
    CubeProblem problem;
    Logger logger;

    CubeGA();
    ~CubeGA();
    void run();
    void setOutputFolder( std::string & path );

private:
    CubeSols genRandSols();
    CubeSols moveFlipMutation( CubeSols & sols, float prob );
    CubeSols cutPointCrossover( CubeSols & sols, float prob );
    CubeSols tournament( CubeSols & sols, uint size, uint num_sols_to_select );
    CubeSols getBest( CubeSols & sols, uint num_of_best );
};


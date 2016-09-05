#pragma once

#include <chrono>
#include <string>
#include <fstream>

#include "cube_sol.hpp"
#include "ga_conf.hpp"
#include "logger.hpp"

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
};


#pragma once

#include <chrono>
#include <string>
#include <fstream>

#include "cube_sol.hpp"
#include "ga_conf.hpp"

class CubeGA
{
public:
    std::chrono::microseconds executionTime;
    CubeGAConfig config;
    CubeSolution best_sol;

    CubeGA();
    ~CubeGA();
    void run();
};


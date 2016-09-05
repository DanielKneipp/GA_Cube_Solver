#pragma once

#include <string>
#include <vector>

#include "cube_prob.hpp"
#include "cube_sol.hpp"
#include "ga_conf.hpp"

class Logger
{
public:
    
    std::string output_file;
    std::string output_folder_file;

    Logger();
    ~Logger();
    void defineOutputFileName( CubeGAConfig & ga_config, CubeProblem & prob );
    void setOutputFolder( const std::string & path );
    void storeStats( std::vector< CubeSolution > sols );
    void plotStoredData();

private:
    std::string output_folder;
};
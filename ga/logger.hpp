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
    void defineOutputFileName( 
        CubeGAConfig & ga_config, 
        CubeProblem & prob 
    );
    void setOutputFolder( const std::string & path );
    void writeHeader();
    void storeStats( 
        std::vector< CubeSolution > & sols, 
        unsigned num_better_children,
        unsigned num_worse_children
    );
    void storeSolution( 
        CubeSolution sol, 
        const std::string & name,
        uint cube_num_moves = 0
    );
    void plotStoredData();

private:
    std::string output_folder;
};
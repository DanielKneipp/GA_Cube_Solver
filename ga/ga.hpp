#pragma once

#include <chrono>
#include <string>
#include <fstream>

#include "cube_sol.hpp"

typedef unsigned int uint;

struct CubeGAConfig
{
    /** Number of individuals */
    uint NUM_INDIV;
    /** Number of generations */
    uint NUM_GENS;
    /** Crossover probability */
    float P_CROSS;
    /** Mutation probability */
    float P_MUT;
    /** Tournament size */
    uint TOURN_SIZE;
    /** Specifies if it should use elitism */
    bool USE_ELIT;
    /** Configuration name */
    std::string CONFIG_NAME;

    bool is_loaded;

    CubeGAConfig()
        : is_loaded( false )
    {}

    void load( const std::string& file_name )
    {
        std::ifstream file( file_name );
        std::string tmpString;

        unsigned short count = 0;

        if( file.is_open() )
        {
            file >> tmpString;
            while( !file.eof() )
            {
                if( tmpString == "NUM_INDIV:" )
                {
                    file >> tmpString;
                    this->NUM_INDIV = static_cast< uint >( std::stoul( tmpString ) );
                    count++;
                }
                if( tmpString == "NUM_GENS:" )
                {
                    file >> tmpString;
                    this->NUM_GENS = static_cast< uint >( std::stoul( tmpString ) );
                    count++;
                }
                else if( tmpString == "P_CROSS:" )
                {
                    file >> tmpString;
                    this->P_CROSS = std::stof( tmpString );
                    count++;
                }
                else if( tmpString == "P_MUT:" )
                {
                    file >> tmpString;
                    this->P_MUT = std::stof( tmpString );
                    count++;
                }
                if( tmpString == "TOURN_SIZE:" )
                {
                    file >> tmpString;
                    this->TOURN_SIZE = static_cast< uint >( std::stoul( tmpString ) );
                    count++;
                }
                if( tmpString == "USE_ELIT:" )
                {
                    file >> tmpString;
                    this->USE_ELIT = static_cast< bool >( std::stoi( tmpString ) );
                    count++;
                }
                else if( tmpString == "CONFIG_NAME:" )
                {
                    file >> tmpString;
                    this->CONFIG_NAME = tmpString;
                    count++;
                }

                file >> tmpString;
            }
        }
        if( count < 7 )
        {
            throw std::invalid_argument( std::string( "The configuration file " ) + file_name +
                " does not have enough parameters to fill CubeGAConfig" );
        }

        this->is_loaded = true;
    }

    std::string toString() const
    {
        return std::string( "NUM_INDIV: " ) + std::to_string( this->NUM_INDIV ) + "\n"
            + std::string( "NUM_GENS: " ) + std::to_string( this->NUM_GENS ) + "\n"
            + std::string( "P_CROSS: " ) + std::to_string( this->P_CROSS ) + "\n"
            + std::string( "P_MUT: " ) + std::to_string( this->P_MUT ) + "\n"
            + std::string( "TOURN_SIZE: " ) + std::to_string( this->TOURN_SIZE ) + "\n"
            + std::string( "USE_ELIT: " ) + std::to_string( this->USE_ELIT ) + "\n"
            + std::string( "CONFIG_NAME: " ) + this->CONFIG_NAME;
    }
};

class CubeGA
{
public:
    std::chrono::microseconds executionTime;
    CubeGAConfig config;
    std::string output_folder;
    CubeSolution best_sol;

    CubeGA();
    ~CubeGA();
    void run();
};


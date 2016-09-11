#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <iterator>

#define _GNUPLOT_SCRIPT_FIT "plot_fit_data.gp" 
#define _GNUPLOT_SCRIPT_IND "plot_ind_data.gp"

std::string getSuffixDateTime()
{
    std::stringstream out;
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t( now );
    out << std::put_time( std::localtime( &now_t ), "%Y-%m-%d_%H-%M-%S" );
    return out.str();
}

Logger::Logger()
    : output_folder( "" )
    , output_file( "" )
    , output_folder_file( "" )
{}

Logger::~Logger()
{}

void Logger::defineOutputFileName( 
    CubeGAConfig & ga_config, 
    CubeProblem & prob 
)
{
    this->output_file = prob.instance_name + "_"
        + ga_config.CONFIG_NAME + "_"
        + getSuffixDateTime()
        + ".log";

    this->output_folder_file = this->output_folder + this->output_file;
}

void Logger::setOutputFolder( const std::string & path )
{
    this->output_folder = path;
    this->output_folder_file = this->output_folder + this->output_file;
}

std::ofstream openOutFile( std::string path_file )
{
    std::ofstream out_file;
    out_file.open( path_file, std::ios::app );

    if( !out_file.is_open() )
    {
        throw std::runtime_error( std::string(
            std::string( "The output file (" ) += path_file += ") couldn't be opened"
        ).c_str() );
    }

    return out_file;
}

void Logger::writeHeader()
{
    std::ofstream out_file = openOutFile( this->output_folder_file );

    out_file << "Max Min Mean Stddev Clones Num_Better_Children Num_Worse_Children\n";

    out_file.close();
}

void Logger::storeStats( 
    std::vector< CubeSolution > & sols, 
    unsigned num_better_children,
    unsigned num_worse_children
)
{
    // Get the best, worst, mean, stddev and number of clones
    std::vector< CubeSolution > sorted_sols = sols;
    std::sort( sorted_sols.begin(), sorted_sols.end() );

    unsigned num_clones = 0;

    float acc = sols[ 0 ].fitness,
        old_f = sols[ 0 ].fitness,
        min = sorted_sols[ 0 ].fitness,
        max = sorted_sols[ sorted_sols.size() - 1 ].fitness;

    for( std::size_t i = 1; i < sorted_sols.size(); ++i )
    {
        float f = sols[ i ].fitness;

        acc += f;

        if( f == old_f )
            num_clones++;

        old_f = f;
    }

    float mean = acc / ( float )sols.size();   

    float accum = 0.0;
    std::for_each( std::begin( sols ), std::end( sols ), [ & ]( const CubeSolution & s )
    {
        accum += ( s.fitness - mean ) * ( s.fitness - mean );
    } );

    float stddev = std::sqrt( accum / ( sols.size() - 1 ) );

    // Write to the output file
    std::ofstream out_file = openOutFile( this->output_folder_file );

    out_file << max << " " 
        << min << " " 
        << mean << " " 
        << stddev << " "
        << num_clones << " " 
        << num_better_children << " " 
        << num_worse_children << "\n";

    out_file.close();
}

void Logger::storeSolution( 
    CubeSolution sol, 
    const std::string & name,
    uint cube_num_sols
)
{
    std::ofstream out_file = openOutFile( this->output_folder_file + ".cubesols" );

    if( cube_num_sols == 0 )
        out_file << name << ": " << sol.toString();
    else // Translate the offset and print smart moves entirely and not its id
        out_file << name << ": " << sol.toString( cube_num_sols ); 

    out_file.close();
}

void Logger::plotStoredData()
{
    // Call gnuplot script

    // gnuplot -e "filename='in1_C1_2015-10-02_20-44-26'" plotGAData.gp
    std::string command;
    command = "gnuplot -e \"";
    command += std::string( "filename='" ) + this->output_folder_file + "'\" ";
    command += _GNUPLOT_SCRIPT_FIT;

    std::system( command.c_str() );

    command = "";
    command = "gnuplot -e \"";
    command += std::string( "filename='" ) + this->output_folder_file + "'\" ";
    command += _GNUPLOT_SCRIPT_IND;

    std::system( command.c_str() );
}

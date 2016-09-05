#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

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

void Logger::defineOutputFileName( CubeGAConfig & ga_config, CubeProblem & prob )
{
    this->output_file = prob.instance_name + "_"
        + ga_config.CONFIG_NAME + "_"
        + getSuffixDateTime();

    this->output_folder_file = this->output_folder + this->output_file;
}

void Logger::setOutputFolder( const std::string & path )
{
    this->output_folder = path;
    this->output_folder_file = this->output_folder + this->output_file;
}

void Logger::storeStats( std::vector<CubeSolution> sols )
{}

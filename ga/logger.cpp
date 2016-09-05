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
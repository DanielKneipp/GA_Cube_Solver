#pragma once

#include <string>

class Logger
{
public:
    std::string output_folder;
    std::string output_file;
    std::string output_folder_file;

    Logger();
    ~Logger();
    void defineOutputFileName();
};
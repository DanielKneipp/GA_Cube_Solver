#include "ga.hpp"

#include <stdexcept>

typedef std::chrono::steady_clock::time_point TimePoint;

inline TimePoint getTimeNow() { return std::chrono::steady_clock::now(); }

CubeGA::CubeGA() {}

CubeGA::~CubeGA() {}

void CubeGA::run()
{
    TimePoint start_t = getTimeNow();

    // Verifies if the configuration was loaded
    if( !this->config.is_loaded )
        throw std::exception( "Configuration wasn't loaded" );

    // TODO: Create output file name with path

    // TODO: Generate individuals

    // TODO: Calculate Fitness

    // Starting evolutionary process

        // TODO: Select Individuals (with or without elitism)

        // TODO: Crossover or mutate the individuals

        // TODO: Calculate Fitness again

        /* TODO: Get the best, worst, mean, number of clones 
           and children better than the mean fitness of their parents*/

    // TODO: Plot the result

    TimePoint end_t = getTimeNow();
}

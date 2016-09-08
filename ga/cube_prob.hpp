#pragma once

#include <string>
#include <vector>

#include "cube/cube.hpp"
#include "cube_sol.hpp"

typedef std::vector< float > kernel_row;
typedef std::vector< kernel_row > kernel_type;

class CubeProblem
{
public:
    Cube cube;
    std::string instance_name;
    bool is_loaded;

    CubeProblem();
    ~CubeProblem();

    void evalSolution( CubeSolution & sol );
    void load( std::string & file );

private:
    kernel_type g_kernel;

    // ********************************************************************************
    /// <summary>
    /// Computes the a modifiedGaussian kernel with 
    /// mu = <paramref name="kernelRadius"/> and 
    /// sigma = <paramref name="kernelRadius"/> / 2.
    /// </summary>
    /// <remarks>
    ///  Reference: http://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel 
    /// (moooeeeep answer).
    /// </remarks>
    /// <param name="kernelRadius"> Radius of the kernel </param>
    /// <created>Daniel Kneipp,9/7/2016</created>
    /// <changed>Daniel Kneipp,9/7/2016</changed>
    // ********************************************************************************
    void genModifiedGaussianKernel( unsigned kernelRadius );
};


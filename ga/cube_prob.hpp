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

    Cube evalSolution( CubeSolution & sol );
    // ********************************************************************************
    /// <summary>
    /// Evaluate the solution getting some statistics from it
    /// </summary>
    /// <param name="moves">Individual chromosome</param>
    /// <param name="fitness">Output parameter with the individual fitness</param>
    /// <param name="num_moves">Output parameter specifying the number of 
    /// movements of the individual</param>
    /// <param name="num_diff_facelets">Output parameter with the number of 
    /// squares that have different color from the center (of their faces)</param>
    /// <param name="freq">Distance metric from the current cube state to 
    /// the desired result (solved cube)</param>
    /// <returns>Resultant cube</returns>
    /// <created>Daniel Kneipp,9/27/2016</created>
    /// <changed>Daniel Kneipp,9/27/2016</changed>
    // ********************************************************************************
    Cube evalSolution( 
        std::vector< int > & moves, 
        float & fitness, 
        uint & num_moves,
        uint & num_diff_facelets,
        uint & freq
    );
    void load( const std::string & file );

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


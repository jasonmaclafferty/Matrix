/*
<Matrix--A matrix algorithm for doing matrix algebra.>
Copyright (C) <2015> <Jason L MacLafferty>
Contact me at: jason.maclafferty.93@gmail.com  

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <Matrix.hpp>
#include <sys/time.h>

int main()
{
    MatrixAlgebra::Matrix<int> matrix1(10000, 10000, 1);
    MatrixAlgebra::Matrix<int> matrix2(10000, 10000, 2);

    // Benchmark parallel addition on 4 threads
    struct timeval computationStartTime, computationEndTime;
    gettimeofday(&computationStartTime, nullptr);
    matrix1.parallelAdd(matrix2, 4);
    gettimeofday(&computationEndTime, nullptr);
    double computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                             (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to add two 10,000 x 10,000 matrices of ints on 4 threads: " << computationTime << "s" << std::endl;

    // Do addition on 1 thread for sake of comparison against multi-threaded version.
    gettimeofday(&computationStartTime, nullptr);
    matrix1.parallelAdd(matrix2, 1);
    gettimeofday(&computationEndTime, nullptr);
    computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                      (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to add two 10,000 x 10,000 matrices of ints on a single thread: " << computationTime << "s" << std::endl;

    // Benchmark parallel multiplication of matrices on 4 threads
    MatrixAlgebra::Matrix<int> matrix3(1000, 1000, 1);
    MatrixAlgebra::Matrix<int> matrix4(1000, 1000, 2);
    MatrixAlgebra::Matrix<int> multOutput1(1000, 1000);

    gettimeofday(&computationStartTime, nullptr);
    matrix3.parallelMultiply(matrix4, multOutput1, 4);
    gettimeofday(&computationEndTime, nullptr);
    computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                      (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to multiply two 1000 x 1000 matrices on 4 threads: " << computationTime << "s" << std::endl;

    // Do matrix multiplication on a single thread to compare with the multi-threaded performance
    gettimeofday(&computationStartTime, nullptr);
    matrix3.parallelMultiply(matrix4, multOutput1, 1);
    gettimeofday(&computationEndTime, nullptr);
    computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                      (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to multiply two 1000 x 1000 matrices of ints on a single thread: " << computationTime << "s" << std::endl;
}

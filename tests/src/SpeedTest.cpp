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

void benchmarkAddition(int numberOfThreads, int numOfRowsAndColumns)
{
    MatrixAlgebra::Matrix<int> matrix1(numOfRowsAndColumns, numOfRowsAndColumns, 3);
    MatrixAlgebra::Matrix<int> matrix2(numOfRowsAndColumns, numOfRowsAndColumns, 6);
    struct timeval computationStartTime, computationEndTime;
    gettimeofday(&computationStartTime, nullptr);
    matrix1.parallelAdd(matrix2, numberOfThreads);
    gettimeofday(&computationEndTime, nullptr);
    double computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                             (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to add two " << numOfRowsAndColumns << " x " << numOfRowsAndColumns << " matrices of ints on " << numberOfThreads << " threads: " 
        << computationTime << "s" << std::endl;
}

void benchmarkMultiplication(int numberOfThreads, int numOfRowsAndColumns)
{
    MatrixAlgebra::Matrix<int> matrix1(numOfRowsAndColumns, numOfRowsAndColumns, 3);
    MatrixAlgebra::Matrix<int> matrix2(numOfRowsAndColumns, numOfRowsAndColumns, 6);
    MatrixAlgebra::Matrix<int> matrixOutput(numOfRowsAndColumns, numOfRowsAndColumns);
    struct timeval computationStartTime, computationEndTime;
    gettimeofday(&computationStartTime, nullptr);
    matrix1.parallelMultiply(matrix2, matrixOutput, numberOfThreads);
    gettimeofday(&computationEndTime, nullptr);
    double computationTime = ((((double) computationEndTime.tv_usec) / ((double) 10e6)) + computationEndTime.tv_sec) -
                             (computationStartTime.tv_sec + (((double) computationStartTime.tv_usec) / ((double) 10e6)));
    std::cout << "Time taken to multiply two " << numOfRowsAndColumns << " x " << numOfRowsAndColumns << " matrices of ints on " << numberOfThreads << " threads: " 
        << computationTime << "s" << std::endl;
}

int main()
{
    // benchmark matrix addition on up to 4 threads
    benchmarkAddition(1, 1000);
    benchmarkAddition(2, 1000);
    benchmarkAddition(4, 1000);
    benchmarkAddition(1, 10000);
    benchmarkAddition(2, 10000);
    benchmarkAddition(4, 10000);
    benchmarkAddition(1, 20000);
    benchmarkAddition(2, 20000);
    benchmarkAddition(4, 20000);
    // benchmark matrix addition on up to 8 threads
    benchmarkAddition(1, 10000);
    benchmarkAddition(8, 10000);
    benchmarkAddition(1, 20000);
    benchmarkAddition(8, 20000);

    // benchmark matrix multiplication  on up to 4 threads
    benchmarkMultiplication(1, 1000);
    benchmarkMultiplication(2, 1000);
    benchmarkMultiplication(4, 1000);
    benchmarkMultiplication(8, 1000);
    benchmarkMultiplication(16, 1000);
}

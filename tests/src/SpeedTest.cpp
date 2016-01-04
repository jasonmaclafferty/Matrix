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

int main()
{
    MatrixAlgebra::Matrix<int> matrix1(10000, 10000, 1);
    MatrixAlgebra::Matrix<int> matrix2(10000, 10000, 2);

    // Benchmark parallel addition on 4 threads
    matrix1.parallelAdd(matrix2, 4);

    // Benchmark parallel multiplication of matrices on 4 threads
    MatrixAlgebra::Matrix<int> matrix3(1000, 1000, 1);
    MatrixAlgebra::Matrix<int> matrix4(1000, 1000, 2);
    MatrixAlgebra::Matrix<int> multOutput1(1000, 1000);
    matrix3.parallelMultiply(matrix4, multOutput1, 4);
}

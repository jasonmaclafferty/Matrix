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
#include <MatrixBase.hpp>
#include <Utility.hpp>

int main()
{
    std::cout << "Begin testing IO capabilities of the MatrixBase class." << std::endl;

    MatrixBase<int> matrix1(9, 9, -2000000000);
    MatrixBase<int> matrix2(20, 20);
    MatrixBase<int> matrix3(15, 27);
    MatrixBase<double> matrix4(20, 20);

    createRandomIntMatrix(matrix2);
    createRandomIntMatrix(matrix3);
    for (unsigned row = 0U; row < 20; row++)
        for (unsigned col = 0U; col < 20; col++)
            matrix4[row][col] = static_cast<double>(matrix2[row][col]) / 3.1588;

    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;
    std::cout << matrix3 << std::endl;
    std::cout << matrix4 << std::endl;
}

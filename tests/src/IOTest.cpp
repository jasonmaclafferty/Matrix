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
#include <fstream>
#include <MatrixBase.hpp>
#include <Utility.hpp>

int main()
{
    std::cout << "Begin testing IO capabilities of the MatrixBase class." << std::endl;

    MatrixBase<int> matrix1(9, 9, -2000000000);
    MatrixBase<int> matrix2(10, 10);
    MatrixBase<int> matrix3(5, 7);
    MatrixBase<double> matrix4(10, 10);
    MatrixBase<int> matrix5(3, 3);

    createRandomIntMatrix(matrix2, -2000000000, 2000000000);
    createRandomIntMatrix(matrix3, -2000000000, 2000000000);
    for (unsigned row = 0U; row < 10; row++)
        for (unsigned col = 0U; col < 10; col++)
            matrix4[row][col] = static_cast<double>(matrix2[row][col]) / 3.1588;
    createRandomIntMatrix(matrix5, -2000000000, 2000000000);

    std::cout << "Test operator<< overload with std::cout" << std::endl;
    std::cout << matrix1 << std::endl;
    std::cout << matrix2 << std::endl;
    std::cout << matrix3 << std::endl;
    std::cout << matrix4 << std::endl;
    std::cout << matrix5 << std::endl;

    createRandomIntMatrix(matrix2, 5, 20);
    createRandomIntMatrix(matrix3, -5, 100);
    createRandomIntMatrix(matrix5, -10000, 12000);
    for (unsigned row = 0U; row < 10; row++)
        for (unsigned col = 0U; col < 10; col++)
            matrix4[row][col] = static_cast<double>(matrix2[row][col]) / 1.719;

    std::ofstream ioTestFile("IOTestFile");
    ioTestFile << "Test operator<< overload for file streams." << std::endl;
    ioTestFile << matrix1 << std::endl;
    ioTestFile << matrix2 << std::endl;
    ioTestFile << matrix3 << std::endl;
    ioTestFile << matrix4 << std::endl;
    ioTestFile << matrix5 << std::endl;

    ioTestFile << "Test the MatrixBase::output member function." << std::endl;
    matrix1.output(ioTestFile, 15);
    matrix2.output(ioTestFile, 2);
    matrix3.output(ioTestFile, 3);
    matrix4.output(ioTestFile, 8);
    matrix5.output(ioTestFile, 6);
    ioTestFile.close();

    std::cout << "Finished testing IO capabilities of the MatrixBase class." << std::endl;
}

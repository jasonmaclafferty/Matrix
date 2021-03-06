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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <Utility.hpp>

namespace MatrixAlgebra
{
    bool isCloseEnough(double expectedVal, double actualVal, double degreeOfAccuracy)
    {
        bool isCloseEnough = false;
        if (fabs(expectedVal - actualVal) <= degreeOfAccuracy)
        {
            isCloseEnough = true;
        }

        return isCloseEnough;
    }

    void createRandomIntMatrix(MatrixAlgebra::MatrixBase<int>& matrix, int lowerBound, int upperBound)
    {
        std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> generator;
        std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
        auto dice                       =   std::bind(distribution, generator);
        unsigned matrixNumOfRows        =   matrix.getNumberOfRows();
        unsigned matrixNumOfColumns     =   matrix.getNumberOfColumns();

        for (unsigned row = 0U; row < matrixNumOfRows; row++)
        {
            for (unsigned col = 0U; col < matrixNumOfColumns; col++)
            {
                matrix[row][col] = dice();
            }
        }
    }
}

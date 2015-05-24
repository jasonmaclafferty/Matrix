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

/*
Function Name: isCloseEnough
Arg1: T expectedVal--float or double value expected
Arg2: T actualVal--actual float or double value
Arg3: T degreeOfAccuracy--float or double value indicating degree of accuracy for comparison of floating point values
Description: Returns a Boolean value indicating whether the input values of type float or double are close enough to the accepted degree of accuracy.
*/
bool isCloseEnough(double expectedVal, double actualVal, double degreeOfAccuracy)
{
    if (fabs(expectedVal - actualVal) <= degreeOfAccuracy)
        return true;
    else
        return false;
}

// fills a supplied matrix with pseudo random integers
void createRandomIntMatrix(MatrixBase<int>& matrix)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-2000000000, 2000000000);
    auto dice                       =   std::bind(distribution, generator);
    unsigned matrixNumOfRows        =   matrix.getNumOfRows();
    unsigned matrixNumOfColumns     =   matrix.getNumOfColumns();

    for (unsigned row = 0U; row < matrixNumOfRows; row++)
        for (unsigned col = 0U; col < matrixNumOfColumns; col++)
            matrix[row][col] = dice();
}

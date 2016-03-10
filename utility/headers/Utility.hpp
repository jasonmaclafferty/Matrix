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

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <cmath>
#include <random>
#include <functional>
#include <MatrixBase.hpp>

namespace MatrixAlgebra
{

    /*
    Function Name: isCloseEnough
    Arg1: T expectedVal--float or double value expected
    Arg2: T actualVal--actual float or double value
    Arg3: T degreeOfAccuracy--float or double value indicating degree of accuracy for comparison of floating point values
    Description: Returns a Boolean value indicating whether the input values of type float or double are close enough to the accepted degree of accuracy.
    */
    bool isCloseEnough(double expectedVal, double actualVal, double degreeOfAccuracy);

    // fills a supplied matrix with pseudo random integers
    void createRandomIntMatrix(MatrixAlgebra::MatrixBase<int>& matrix, int lowerBound, int upperBound);
}

#endif

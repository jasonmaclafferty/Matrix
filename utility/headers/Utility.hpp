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

bool isCloseEnough(double expectedVal, double actualVal, double degreeOfAccuracy);

void createRandomIntMatrix(MatrixAlgebra::MatrixBase<int>& matrix, int lowerBound, int upperBound);

#endif

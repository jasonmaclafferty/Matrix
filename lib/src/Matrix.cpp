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

#include "Matrix.hpp"

template <typename ElemType>
void Matrix<ElemType>::power(unsigned exponent)
{

}

template <typename ElemType>
void Matrix<ElemType>::multiply(const Matrix<ElemType>& matrix2)
{

}

template <typename ElemType>
void Matrix<ElemType>::add(const Matrix<ElemType>& matrix2)
{

}

template <typename ElemType>
void Matrix<ElemType>::subtract(const Matrix<ElemType>& matrix2)
{

}

template <typename ElemType>
void Matrix<ElemType>::multiplyRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd)
{

}

template <typename ElemType>
void Matrix<ElemType>::addRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd)
{

}

template <typename ElemType>
void Matrix<ElemType>::subtractRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd)
{

}

template <typename ElemType>
void Matrix<ElemType>::scale(ElemType scaleFactor)
{

}

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<unsigned>;

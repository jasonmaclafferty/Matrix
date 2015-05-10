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

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "MatrixBase.hpp"

template <typename ElemType>
class Matrix : public MatrixBase<ElemType>
{
    public:
        void power(unsigned exponent);

        void multiply(const Matrix<ElemType>& matrix2);

        void add(const Matrix<ElemType>& matrix2);

        void subtract(const Matrix<ElemType>& matrix2);

        void multiplyRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);

        void addRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);

        void subtractRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);
        
        void scale(ElemType scaleFactor);

        Matrix<ElemType>& operator+(const Matrix<ElemType>& matrix2);

        Matrix<ElemType>& operator-(const Matrix<ElemType>& matrix2);

        Matrix<ElemType>& operator*(const Matrix<ElemType>& matrix2);
};

#endif

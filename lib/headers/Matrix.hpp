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

#include <memory>
#include <MatrixBase.hpp>

template <typename ElemType>
class Matrix : public MatrixBase<ElemType>
{
    protected:
        void parallelAddSubtractHelper(void (Matrix<ElemType>::*func)(const Matrix<ElemType>&, unsigned, unsigned), 
                                      const Matrix<ElemType>& matrix2, unsigned numOfThreads);

    public:
        Matrix(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal) : MatrixBase<ElemType>(numberOfRows, numberOfColumns, elemInitVal) {}
        
        Matrix(unsigned numberOfRows, unsigned numberOfColumns) : MatrixBase<ElemType>(numberOfRows, numberOfColumns) {}

        void power(double exponent);

        std::shared_ptr< Matrix<ElemType> > multiply(const Matrix<ElemType>& matrix2);

        void add(const Matrix<ElemType>& matrix2);

        void subtract(const Matrix<ElemType>& matrix2);

        void multiplyRange(unsigned thisRowStart, unsigned thisRowEnd, const Matrix<ElemType>& matrix2, 
                           unsigned matrix2ColStart, unsigned matrix2ColEnd, Matrix<ElemType>& out);

        void addRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);

        void subtractRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);
        
        void parallelAdd(const Matrix<ElemType>& matrix2, unsigned numOfThreads);

        void parallelSubtract(const Matrix<ElemType>& matrix2, unsigned numOfThreads);

        void scale(ElemType scaleFactor);

        std::shared_ptr< Matrix<ElemType> > operator+(const Matrix<ElemType>& matrix2);

        std::shared_ptr< Matrix<ElemType> > operator-(const Matrix<ElemType>& matrix2);

        std::shared_ptr< Matrix<ElemType> > operator*(const Matrix<ElemType>& matrix2);

        Matrix<ElemType>& operator=(Matrix<ElemType>& matrix2);

        friend std::ostream& operator<<(std::ostream& out, Matrix<ElemType>& matrix) 
        { 
            return out << dynamic_cast< MatrixBase<ElemType>& >(matrix); 
        }
};

#endif

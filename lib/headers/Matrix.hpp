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

namespace MatrixAlgebra
{
    template <typename ElemType>
    class Matrix : public MatrixBase<ElemType>
    {
        // declare member functions for Matrix<ElemType>
        protected:
            // This member function does all of the work for both parallel addition and parallel subtraction.
            void parallelAddSubtractHelper(void (Matrix<ElemType>::*func)(const Matrix<ElemType>&, unsigned, unsigned), 
                                          const Matrix<ElemType>& matrix2, unsigned numOfThreads);

            // Protected member function to help with determining the workload of each thread used in computation.
            void calculateNumberOfRowsPerThread(std::vector<unsigned>& numberOfRowsPerThread, unsigned numberOfThreads);
        public:
            // Constructors
            Matrix(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal) : MatrixBase<ElemType>(numberOfRows, numberOfColumns, elemInitVal) {}
            
            Matrix(unsigned numberOfRows, unsigned numberOfColumns) : MatrixBase<ElemType>(numberOfRows, numberOfColumns) {}

            // Copy constructor
            Matrix(const Matrix<ElemType>& matrixToCopyFrom) : MatrixBase<ElemType>(matrixToCopyFrom) {} 

            // Raises each element of the matrix pointed to by "this" to the power given.
            void power(double exponent);


            // Adds the value of each element matrix2 to the value of each element in "this" and stores the resultant values back in "this".
            void add(const Matrix<ElemType>& matrix2);

            // Subtracts the value of each element matrix2 to the value of each element in "this" and stores the resultant values back in "this".
            void subtract(const Matrix<ElemType>& matrix2);

            // Multiplies the specified row/column ranges of two matrices, "this" and "matrix2", and stores the result in the matrix refered to by "out".
            // The member function will do nothing if given row/column indices which are out of range or the matrix "out" has the incorrect dimensions.
            // indices specified by "thisRowStart", "thisRowEnd", "matrix2ColStart", and "matrix2ColEnd" are zero-based.
            void multiplyRange(unsigned thisRowStart, unsigned thisRowEnd, const Matrix<ElemType>& matrix2, 
                               unsigned matrix2ColStart, unsigned matrix2ColEnd, Matrix<ElemType>& out);

            // Multiplies the martricies matrix2 and "this" if they are of compatible dimensions, and returns a smart pointer to the resultant matrix.
            std::shared_ptr< Matrix<ElemType> > multiply(const Matrix<ElemType>& matrix2);

            // Adds the specified rows of the matrices referred to by "this" and "matrix2" and stores the result in the "this" matrix.
            // "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be added.
            // The matrices referred to by "this" and "matrix2" must have the same dimensions or the member function will do nothing.
            void addRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);
            
            // Subtracts the specified rows of the matrices referred to by "this" and "matrix2" and stores the result in the "this" matrix.
            // "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be subtracted.
            // The matrices referred to by "this" and "matrix2" must have the same dimensions or the member function will do nothing.
            void subtractRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd);
            
            // Parallel add matrix "this" and "matrix2" on the specified number of threads and store the result back in matrix "this" 
            void parallelAdd(const Matrix<ElemType>& matrix2, unsigned numOfThreads);

            // Parallel subtract matrix "this" and "matrix2" on the specified number of threads and store the result back in matrix "this" 
            void parallelSubtract(const Matrix<ElemType>& matrix2, unsigned numOfThreads);

            // scales all the elements in the matrix "this" by a constant factor
            void scale(ElemType scaleFactor);

            // Parallel multiply the matricies "this" and "matrix2" on the specified number of threads and store the output in matrix "out."
            void parallelMultiply(const Matrix<ElemType>& matrix2, Matrix<ElemType>& out, unsigned numberOfThreads);

            // Overload operator+ to add to matrices ("this" and "matrix2"), store the result in a heap allocated matrix, and return the result.
            // A matrix of all zero's with the dimensions the same as "matrix2" will be returned if the dimensions of "this" and "matrix2" do not match.
            std::shared_ptr< Matrix<ElemType> > operator+(const Matrix<ElemType>& matrix2);

            // Overload operator- to subtract to matrices ("this" and "matrix2"), store the result in a heap allocated matrix, and return the result.
            // A matrix of all zero's with the dimensions the same as "matrix2" will be returned if the dimensions of "this" and "matrix2" do not match.
            std::shared_ptr< Matrix<ElemType> > operator-(const Matrix<ElemType>& matrix2);

            // Overload operator* to multiply two matricies ("this" and "matrix2") and return a smart pointer to the result.
            // A zero matrix of dimensions thisNumOfRows x matrix2NumOfColumns will be returned if the inner dimensions of "this" and "matrix2" do not match.
            std::shared_ptr< Matrix<ElemType> > operator*(const Matrix<ElemType>& matrix2);

            // overload the assignment operator for Matrix<ElemType>
            Matrix<ElemType>& operator=(Matrix<ElemType>& matrix2);

    };
    // overload stream insertion operator for std::ostream
    template <typename ElemType>
    std::ostream& operator<<(std::ostream& out, Matrix<ElemType>& matrix) 
    { 
        return out << dynamic_cast< MatrixBase<ElemType>& >(matrix); 
    }
}

#endif

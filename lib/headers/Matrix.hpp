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
    template <typename ElementType>
    class Matrix : public MatrixBase<ElementType>
    {
        // declare member functions for Matrix<ElementType>
        protected:
            // This member function does all of the work for both parallel addition and parallel subtraction.
            void parallelAddSubtractHelper(void (Matrix<ElementType>::*func)(const Matrix<ElementType>&, unsigned, unsigned), 
                                           const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads);

            // Protected member function to help with determining the workload of each thread used in computation.
            void calculateNumberOfRowsPerThread(std::vector<unsigned>& numberOfRowsPerThread, unsigned numberOfThreads);
        public:
            // Constructors
            Matrix(unsigned numberOfRows, unsigned numberOfColumns, ElementType elementInitializationValue) : 
                MatrixBase<ElementType>(numberOfRows, numberOfColumns, elementInitializationValue) {}
            
            Matrix(unsigned numberOfRows, unsigned numberOfColumns) : MatrixBase<ElementType>(numberOfRows, numberOfColumns) {}

            // Copy constructor
            Matrix(const Matrix<ElementType>& matrixToCopyFrom) : MatrixBase<ElementType>(matrixToCopyFrom) {} 

            // Raises each element of the matrix pointed to by "this" to the power given.
            void power(double exponent);


            // Adds the value of each element otherMatrix to the value of each element in "this" and stores the resultant values back in "this".
            void add(const Matrix<ElementType>& otherMatrix);

            // Subtracts the value of each element otherMatrix to the value of each element in "this" and stores the resultant values back in "this".
            void subtract(const Matrix<ElementType>& otherMatrix);

            // Multiplies the specified row/column ranges of two matrices, "this" and "otherMatrix", and stores the result in the matrix refered to by "out".
            // The member function will do nothing if given row/column indices which are out of range or the matrix "out" has the incorrect dimensions.
            // indices specified by "thisRowStart", "thisRowEnd", "otherMatrixColStart", and "otherMatrixColEnd" are zero-based.
            void multiplyRange(unsigned thisRowStart, unsigned thisRowEnd, const Matrix<ElementType>& otherMatrix, 
                               unsigned otherMatrixColStart, unsigned otherMatrixColEnd, Matrix<ElementType>& out);

            // Multiplies the martricies otherMatrix and "this" if they are of compatible dimensions, and returns a smart pointer to the resultant matrix.
            std::shared_ptr< Matrix<ElementType> > multiply(const Matrix<ElementType>& otherMatrix);

            // Adds the specified rows of the matrices referred to by "this" and "otherMatrix" and stores the result in the "this" matrix.
            // "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be added.
            // The matrices referred to by "this" and "otherMatrix" must have the same dimensions or the member function will do nothing.
            void addRange(const Matrix<ElementType>& otherMatrix, unsigned rowStart, unsigned rowEnd);
            
            // Subtracts the specified rows of the matrices referred to by "this" and "otherMatrix" and stores the result in the "this" matrix.
            // "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be subtracted.
            // The matrices referred to by "this" and "otherMatrix" must have the same dimensions or the member function will do nothing.
            void subtractRange(const Matrix<ElementType>& otherMatrix, unsigned rowStart, unsigned rowEnd);
            
            // Parallel add matrix "this" and "otherMatrix" on the specified number of threads and store the result back in matrix "this" 
            void parallelAdd(const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads);

            // Parallel subtract matrix "this" and "otherMatrix" on the specified number of threads and store the result back in matrix "this" 
            void parallelSubtract(const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads);

            // scales all the elements in the matrix "this" by a constant factor
            void scale(ElementType scaleFactor);

            // Parallel multiply the matricies "this" and "otherMatrix" on the specified number of threads and store the output in matrix "out."
            void parallelMultiply(const Matrix<ElementType>& otherMatrix, Matrix<ElementType>& out, unsigned numberOfThreads);

            // Overload operator+ to add to matrices ("this" and "otherMatrix"), store the result in a heap allocated matrix, and return the result.
            // A matrix of all zero's with the dimensions the same as "otherMatrix" will be returned if the dimensions of "this" and "otherMatrix" do not match.
            std::shared_ptr< Matrix<ElementType> > operator+(const Matrix<ElementType>& otherMatrix);

            // Overload operator- to subtract to matrices ("this" and "otherMatrix"), store the result in a heap allocated matrix, and return the result.
            // A matrix of all zero's with the dimensions the same as "otherMatrix" will be returned if the dimensions of "this" and "otherMatrix" do not match.
            std::shared_ptr< Matrix<ElementType> > operator-(const Matrix<ElementType>& otherMatrix);

            // Overload operator* to multiply two matricies ("this" and "otherMatrix") and return a smart pointer to the result.
            // A zero matrix of dimensions thisNumOfRows x otherMatrixNumOfColumns will be returned if the inner dimensions of "this" and "otherMatrix" do not match.
            std::shared_ptr< Matrix<ElementType> > operator*(const Matrix<ElementType>& otherMatrix);

            // overload the assignment operator for Matrix<ElementType>
            Matrix<ElementType>& operator=(Matrix<ElementType>& otherMatrix);

    };
    // overload stream insertion operator for std::ostream
    template <typename ElementType>
    std::ostream& operator<<(std::ostream& out, Matrix<ElementType>& matrix) 
    { 
        return out << dynamic_cast< MatrixBase<ElementType>& >(matrix); 
    }
}

#endif

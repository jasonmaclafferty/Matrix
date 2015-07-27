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

#include <thread>
#include <cmath>
#include <Matrix.hpp>

// Raises each element of the matrix pointed to by "this" to the power given.
template <typename ElemType>
void Matrix<ElemType>::power(double exponent)
{
    for (unsigned row = 0U; row < this->numOfRows; row++)
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            (*this)[row][col] = static_cast<ElemType>(pow(static_cast<double>((*this)[row][col]), exponent));
}

template <typename ElemType>
void Matrix<ElemType>::add(const Matrix<ElemType>& matrix2){ this->addRange(matrix2, 0, this->numOfRows - 1U); }

template <typename ElemType>
void Matrix<ElemType>::subtract(const Matrix<ElemType>& matrix2){ this->subtractRange(matrix2, 0, this->numOfRows - 1U); }

// Multiplies the specified row/column ranges of two matrices, "this" and "matrix2", and stores the result in the matrix refered to by "out".
// The member function will do nothing if given row/column indices which are out of range or the matrix "out" has the incorrect dimensions.
// indices specified by "thisRowStart", "thisRowEnd", "matrix2ColStart", and "matrix2ColEnd" are zero-based.
template <typename ElemType>
void Matrix<ElemType>::multiplyRange(unsigned thisRowStart, unsigned thisRowEnd, const Matrix<ElemType>& matrix2, 
                                     unsigned matrix2ColStart, unsigned matrix2ColEnd, Matrix<ElemType>& out)
{
    if (out.getNumOfRows() == this->numOfRows && out.getNumOfColumns() == matrix2.getNumOfColumns())
    {
        if (thisRowEnd < this->numOfRows && matrix2ColEnd < matrix2.getNumOfColumns())
        {
            if (this->numOfColumns == matrix2.getNumOfRows())
            {
                for (unsigned outRow = thisRowStart; outRow <= thisRowEnd; outRow++)
                {
                    for (unsigned outCol = matrix2ColStart; outCol <= matrix2ColEnd; outCol++)
                    {
                        for (unsigned productCtr = 0; productCtr < this->numOfColumns; productCtr++)
                        {
                            if (productCtr == 0)
                                out[outRow][outCol] = (*this)[outRow][productCtr] * matrix2[productCtr][outCol];
                            else
                                out[outRow][outCol] += (*this)[outRow][productCtr] * matrix2[productCtr][outCol];
                        }
                    }
                }
            }
        }
    }
}

template <typename ElemType>
std::shared_ptr< Matrix<ElemType> > Matrix<ElemType>::multiply(const Matrix<ElemType>& matrix2)
{
    std::shared_ptr< Matrix<ElemType> > retval = std::make_shared< Matrix<ElemType> >(this->numOfRows, matrix2.getNumOfColumns());
    this->multiplyRange(0, this->numOfRows - 1U, matrix2, 0, matrix2.getNumOfColumns() - 1U, *retval);

    return retval;
}

// Adds the specified rows of the matrices referred to by "this" and "matrix2" and stores the result in the "this" matrix.
// "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be added.
// The matrices referred to by "this" and "matrix2" must have the same dimensions or the member function will do nothing.
template <typename ElemType>
void Matrix<ElemType>::addRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd)
{
    if (this->numOfColumns == matrix2.getNumOfColumns() && this->numOfRows == matrix2.getNumOfRows())
        if (rowEnd < this->numOfRows)
            for (unsigned row = rowStart; row <= rowEnd; row++)
                for (unsigned col = 0U; col < this->numOfColumns; col++)
                    (*this)[row][col] += matrix2[row][col];   
}

// Subtracts the specified rows of the matrices referred to by "this" and "matrix2" and stores the result in the "this" matrix.
// "rowStart" and "rowEnd" are zero-based indices for the desired rows of both matrices to be added.
// The matrices referred to by "this" and "matrix2" must have the same dimensions or the member function will do nothing.
template <typename ElemType>
void Matrix<ElemType>::subtractRange(const Matrix<ElemType>& matrix2, unsigned rowStart, unsigned rowEnd)
{
    if (this->numOfColumns == matrix2.getNumOfColumns() && this->numOfRows == matrix2.getNumOfRows())
        if (rowEnd < this->numOfRows)
            for (unsigned row = rowStart; row <= rowEnd; row++)
                for (unsigned col = 0U; col < this->numOfColumns; col++)
                    (*this)[row][col] -= matrix2[row][col];   
}

// scales all the elements in the matrix "this" by a constant factor
template <typename ElemType>
void Matrix<ElemType>::scale(ElemType scaleFactor)
{
    for (unsigned row = 0U; row < this->numOfRows; row++)
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            (*this)[row][col] *= scaleFactor;
}

// overload the assignment operator
template <typename ElemType>
Matrix<ElemType>& Matrix<ElemType>::operator=(Matrix<ElemType>& matrix2)
{
    MatrixBase<ElemType>& matrix2Temp    =  matrix2; 
    MatrixBase<ElemType>& thisTemp       =  *this; 
    thisTemp                             =   matrix2Temp;

    return dynamic_cast< Matrix<ElemType>& >(thisTemp);
}

// Overload operator+ to add to matrices ("this" and "matrix2"), store the result in a heap allocated matrix, and return the result.
// A matrix of all zero's with the dimensions the same as "matrix2" will be returned if the dimensions of "this" and "matrix2" do not match.
template <typename ElemType>
std::shared_ptr< Matrix<ElemType> > Matrix<ElemType>::operator+(const Matrix<ElemType>& matrix2)
{
    unsigned matrix2NumOfRows = matrix2.getNumOfRows(), matrix2NumOfColumns = matrix2.getNumOfColumns();
    std::shared_ptr< Matrix<ElemType> > retval = std::make_shared< Matrix<ElemType> >(matrix2NumOfRows, matrix2NumOfColumns);

    if (this->numOfRows == matrix2NumOfRows && this->numOfColumns == matrix2NumOfColumns)
        for (unsigned row = 0U; row < this->numOfRows; row++)
            for (unsigned col = 0U; col < this->numOfColumns; col++)
                (*retval)[row][col] = (*this)[row][col] + matrix2[row][col];

    return retval;
}

// Overload operator- to subtract to matrices ("this" and "matrix2"), store the result in a heap allocated matrix, and return the result.
// A matrix of all zero's with the dimensions the same as "matrix2" will be returned if the dimensions of "this" and "matrix2" do not match.
template <typename ElemType>
std::shared_ptr< Matrix<ElemType> > Matrix<ElemType>::operator-(const Matrix<ElemType>& matrix2)
{
    unsigned matrix2NumOfRows = matrix2.getNumOfRows(), matrix2NumOfColumns = matrix2.getNumOfColumns();
    std::shared_ptr< Matrix<ElemType> > retval = std::make_shared< Matrix<ElemType> >(matrix2NumOfRows, matrix2NumOfColumns);

    if (this->numOfRows == matrix2NumOfRows && this->numOfColumns == matrix2NumOfColumns)
        for (unsigned row = 0U; row < this->numOfRows; row++)
            for (unsigned col = 0U; col < this->numOfColumns; col++)
                (*retval)[row][col] = (*this)[row][col] - matrix2[row][col];

    return retval;

}

// Overload operator* to multiply two matricies ("this" and "matrix2") and return a smart pointer to the result.
// A zero matrix of dimensions thisNumOfRows x matrix2NumOfColumns will be returned if the inner dimensions of "this" and "matrix2" do not match.
template <typename ElemType>
std::shared_ptr< Matrix<ElemType> > Matrix<ElemType>::operator*(const Matrix<ElemType>& matrix2)
{
    unsigned matrix2NumOfColumns = matrix2.getNumOfColumns();
    auto retval = std::make_shared< Matrix<ElemType> >(this->numOfRows, matrix2.getNumOfColumns());
    this->multiplyRange(0, this->numOfRows - 1U, matrix2, 0, matrix2NumOfColumns - 1U, *retval);

    return retval;
}

// Parallel add matrix "this" and "matrix2" and store back in matrix "this" on the specified number of threads
template <typename ElemType>
void Matrix<ElemType>::parallelAdd(const Matrix<ElemType>& matrix2, unsigned numOfThreads)
{
    this->parallelAddSubtractHelper(&Matrix<ElemType>::addRange, matrix2, numOfThreads);
}

// Parallel subtract matrix "this" and "matrix2" and store the result back in matrix "this" on the specified number of threads
template <typename ElemType>
void Matrix<ElemType>::parallelSubtract(const Matrix<ElemType>& matrix2, unsigned numOfThreads)
{
    this->parallelAddSubtractHelper(&Matrix<ElemType>::subtractRange, matrix2, numOfThreads);
}

template <typename ElemType>
void Matrix<ElemType>::parallelAddSubtractHelper(void (Matrix<ElemType>::*func)(const Matrix<ElemType>&, unsigned, unsigned), 
                                                 const Matrix<ElemType>& matrix2, unsigned numOfThreads)
{
    unsigned matrix2NumOfRows       =   matrix2.getNumOfRows();
    unsigned matrix2NumOfColumns    =   matrix2.getNumOfColumns();
    
    if (this->numOfRows == matrix2NumOfRows && this->numOfColumns == matrix2NumOfColumns)
    {
        std::vector<unsigned> rowsPerThread;
        for (unsigned i = 0; i < numOfThreads; i++)
            rowsPerThread.push_back(0);
        for (unsigned& rowsPerThreadElem : rowsPerThread)
            rowsPerThreadElem = this->numOfRows / numOfThreads; // divide the number of rows to do the arithmetic on by the number of threads doing work

        unsigned numOfLeftOverRows  =   this->numOfRows % numOfThreads; // the number of rows from the matrices that do not evenly divide by the number of threads
        bool done                   =   (numOfLeftOverRows != 0) ? false : true;
        while (!done)
        {
            for (unsigned& elem : rowsPerThread)
            {
                if (numOfLeftOverRows > 0)
                {
                    elem++;
                    numOfLeftOverRows--;
                }
                else
                {
                    done = true;
                    break;
                }
            }
        }

        // spawn threads to do the arithmetic
        unsigned rowStart = 0;
        for (unsigned threadPos = 0; threadPos < numOfThreads - 1U; threadPos++)
        {
            std::thread currThread{func, this, matrix2, rowStart, rowStart + (rowsPerThread[threadPos] - 1U)};
            rowStart += rowsPerThread[threadPos];
            currThread.join();
        }

        // do part of the arithmetic on the main thread
        (this->*func)(matrix2, rowStart, rowStart + (rowsPerThread[numOfThreads - 1U] - 1U));
    }
}

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<unsigned>;

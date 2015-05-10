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

#include "MatrixBase.hpp"
#include "Utility.hpp"

// Assigns the value "newElemVal" to the matrix element at position "row", "col" if a valid row and column are given--otherwise nothing is done.
template <typename ElemType>
void MatrixBase<ElemType>::setElement(unsigned row, unsigned col, ElemType newElemVal)
{
    if (row < this->getNumOfRows() && col < this->getNumOfColumns())
        this->data[row][col] = newElemVal;
}

// Returns the matrix element at position "row", "col" if  given a valid row, col position--otherwise the return value is unspecified.
template <typename ElemType>
ElemType MatrixBase<ElemType>::getElement(unsigned row, unsigned col) const
{
    ElemType retval;
    if (row < this->getNumOfRows() && col < this->getNumOfColumns())
        retval = this->data[row][col];

    return retval;
}

// MatrixBase class constructor accepting parameters specified the desired number of rows and columns for the matrix.
template <typename ElemType>
MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns)
{
    this->init(numberOfRows, numberOfColumns, 0);
}

// MatrixBase class constructor accepting as arguments the desired number of rows and columns .
// for the matrix to be created along with what value each matrix element should have.
template <typename ElemType>
MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal) 
{ 
    this->init(numberOfRows, numberOfColumns, elemInitVal); 
}

// Initialization function which does all of the heavy lifting for the MatrixBase class constructors.
template <typename ElemType>
void MatrixBase<ElemType>::init(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal)
{
    this->numOfRows     =   numberOfRows;
    this->numOfColumns  =   numberOfColumns;
    std::vector<ElemType> temp;

    for (unsigned i = 0; i < numberOfColumns; i++)
        temp.push_back(elemInitVal);

    for (unsigned i = 0; i < numberOfRows; i++)
        this->data.push_back(temp);
}

// Returns a Boolean value indicating whether or not the matrix is the identity matrix.
// An identity matrix is defined to have the value of 1 for all the elements along the matrix diagonal and 0's everywhere else.
// Additionally, all identity matricies are square--that is the number of rows = the number of columns.
// For matricies containing float or double values, an identity matrix is guaranteed to have values along the diagonal equal to 1 +/- 0.000001.
// Matricies of int or unsigned values are guaranteed to have values of exactly 1 along the diagonal if they are identity matricies.
template <typename ElemType>
bool MatrixBase<ElemType>::isIdentity()
{
    if (this->numOfRows == this->numOfColumns)
    {
        for (unsigned row = 0U; row < this->numOfRows; row++)
            if (!isCloseEnough(static_cast<double>(this->getElement(row, row)), 1, 0.000001))
                return false;
    }
    else
    {
        return false; // numOfRows != numOfColumns = !identity
    }

    return true; // The matrix is the identity matrix. 
}

// Returns a Boolean value indicating whether or not the matrix is the Zero Matrix.
// The Zero Matrix is defined a matrix containing all zero values for all of its elements.
// For matricies of int or unsigned values, zero matricies are guaranteed to have all elements with a value of exactly 0.
// For matricies of double or float values, all elements are guaranteed to have values of 0 +/- 0.000001
template <typename ElemType>
bool MatrixBase<ElemType>::isZero()
{
    for (unsigned row = 0U; row < this->numOfRows; row++)
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            if (!isCloseEnough(this->getElement(row, col), 0, 0.000001))
                return false; // A non-zero value was found. So, the matrix does not constitute the zero matrix.

    return true; // All of the matrix elements are 0.
}

// Returns the Boolean result of comparing two matricies for equality. Two matrices are considered equal if they have the same dimensions
// and all of their corresponding elements are equal.
// If matricies of int or unsigned values are equal, then their corresponding values are guaranteed to be exactly equal.
// Otherwise, if the matricies contain values of type double or float, then corresponding values will be within +/- 0.000001 of each other for equal matricies.
template <typename ElemType>
bool MatrixBase<ElemType>::equal(const MatrixBase<ElemType>& matrix) const
{
    if (this->getNumOfRows() == matrix.getNumOfRows() && this->getNumOfColumns() == matrix.getNumOfColumns())
    {
        for (unsigned row = 0U; row < this->getNumOfRows(); row++)
            for (unsigned col = 0U; col < this->getNumOfColumns(); col++)
                if (!isCloseEnough(static_cast<double>(this->getElement(row, col)), static_cast<double>(matrix[row][col]), 0.000000000001))
                    return false; // Matrices are not equal because one of the pairs of matrix elements are not equal.
    }
    else
    {
        return false; // Matrices are not equal because the dimensions are not equal.
    }

    return true; // If the dimensions match and all the elements are equal, then the matrices are equal.
}

// Overload for operator<< to allow writing a matrix to an output stream such as a file or the console.
template <typename ElemType>
std::ostream& operator<<(std::ostream& out, const MatrixBase<ElemType>& matrix)
{

    return out; // Stub to implement later.
}

// A convenient operator overload to compare to matrix objects for equality.
template <typename ElemType>
bool MatrixBase<ElemType>::operator==(const MatrixBase<ElemType>& matrix)
{
    return this->equal(matrix);
}

// Overload operator!= to compare two matricies for negated equality
template <typename ElemType>
bool MatrixBase<ElemType>::operator!=(const MatrixBase<ElemType>& matrix)
{
    return !(*this == matrix);
}

// Overload operator= to allow copying the contents of one matrix to another.
template <typename ElemType>
MatrixBase<ElemType>& MatrixBase<ElemType>::operator=(const MatrixBase<ElemType>& matrix2)
{

    return *this; // Stub to implement later.
}

// Overload operator[] to allow indexing of a matrix like this MatrixBaseInstance[row][col]
template <typename ElemType>
std::vector<ElemType>& MatrixBase<ElemType>::operator[](std::size_t row) { return this->data[row]; }

// Overload operator[] to allow read-only indexing of a matrix
template <typename ElemType>
const std::vector<ElemType>& MatrixBase<ElemType>::operator[](std::size_t row) const { return this->data[row]; }

// Return the number of rows in the matrix.
template <typename ElemType>
unsigned MatrixBase<ElemType>::getNumOfRows() const { return this->numOfRows; }

// Return the number of columns in the matrix.
template <typename ElemType>
unsigned MatrixBase<ElemType>::getNumOfColumns() const { return this->numOfColumns; }

// Returns a Boolean value indicating whether or not a matrix is square. A matrix is considered square if the number of rows equals the number of columns.
template <typename ElemType>
bool MatrixBase<ElemType>::isSquare() { return this->numOfColumns == this->numOfRows; }

template class MatrixBase<int>;
template class MatrixBase<double>;
template class MatrixBase<unsigned>;
template class MatrixBase<float>;

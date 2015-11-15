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

#include <MatrixBase.hpp>
#include <Utility.hpp>

// Copy Constructor
template <typename ElemType>
MatrixAlgebra::MatrixBase<ElemType>::MatrixBase(const MatrixAlgebra::MatrixBase<ElemType>& matrixToCopyFrom)
{
    this->numOfRows     =   matrixToCopyFrom.getNumOfRows();
    this->numOfColumns  =   matrixToCopyFrom.getNumOfColumns();
    std::vector<ElemType> temp;
    for (unsigned i = 0; i < numOfColumns; i++)
        temp.push_back(0);
    for (unsigned row = 0; row < this->numOfRows; row++)
        this->data.push_back(temp);
    for (unsigned row = 0; row < this->numOfRows; row++)
        for (unsigned col = 0; col < this->numOfColumns; col++)
            (*this)[row][col] = matrixToCopyFrom[row][col];
}

// Assigns the value "newElemVal" to the matrix element at position "row", "col" if a valid row and column are given--otherwise nothing is done.
template <typename ElemType>
void MatrixAlgebra::MatrixBase<ElemType>::setElement(unsigned row, unsigned col, ElemType newElemVal)
{
    if (row < this->numOfRows && col < this->numOfColumns)
        this->data[row][col] = newElemVal;
}

// Returns the matrix element at position "row", "col" if  given a valid row, col position--otherwise the return value is unspecified.
template <typename ElemType>
ElemType MatrixAlgebra::MatrixBase<ElemType>::getElement(unsigned row, unsigned col) const
{
    ElemType retval;
    if (row < this->numOfRows && col < this->numOfColumns)
        retval = this->data[row][col];

    return retval;
}

// MatrixBase class constructor accepting parameters specified the desired number of rows and columns for the matrix.
template <typename ElemType>
MatrixAlgebra::MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns)
{
    this->init(numberOfRows, numberOfColumns, 0);
}

// MatrixBase class constructor accepting as arguments the desired number of rows and columns .
// for the matrix to be created along with what value each matrix element should have.
template <typename ElemType>
MatrixAlgebra::MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal) 
{ 
    this->init(numberOfRows, numberOfColumns, elemInitVal); 
}

// Initialization function which does all of the heavy lifting for the MatrixBase class constructors.
template <typename ElemType>
void MatrixAlgebra::MatrixBase<ElemType>::init(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal)
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
bool MatrixAlgebra::MatrixBase<ElemType>::isIdentity()
{
    if (this->numOfRows == this->numOfColumns)
    {
        for (unsigned row = 0U; row < this->numOfRows; row++)
            if (!MatrixAlgebra::isCloseEnough(static_cast<double>(this->getElement(row, row)), 1, 0.000001))
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
bool MatrixAlgebra::MatrixBase<ElemType>::isZero()
{
    for (unsigned row = 0U; row < this->numOfRows; row++)
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            if (!MatrixAlgebra::isCloseEnough(this->getElement(row, col), 0, 0.000001))
                return false; // A non-zero value was found. So, the matrix does not constitute the zero matrix.

    return true; // All of the matrix elements are 0.
}

// Returns the Boolean result of comparing two matricies for equality. Two matrices are considered equal if they have the same dimensions
// and all of their corresponding elements are equal.
// If matricies of int or unsigned values are equal, then their corresponding values are guaranteed to be exactly equal.
// Otherwise, if the matricies contain values of type double or float, then corresponding values will be within +/- 0.000001 of each other for equal matricies.
template <typename ElemType>
bool MatrixAlgebra::MatrixBase<ElemType>::equal(const MatrixAlgebra::MatrixBase<ElemType>& matrix) const
{
    if (this->numOfRows == matrix.getNumOfRows() && this->numOfColumns == matrix.getNumOfColumns())
    {
        for (unsigned row = 0U; row < this->numOfRows; row++)
            for (unsigned col = 0U; col < this->numOfColumns; col++)
                if (!MatrixAlgebra::isCloseEnough(static_cast<double>(this->getElement(row, col)), static_cast<double>(matrix[row][col]), 0.000000000001))
                    return false; // Matrices are not equal because one of the pairs of matrix elements are not equal.
    }
    else
    {
        return false; // Matrices are not equal because the dimensions are not equal.
    }

    return true; // If the dimensions match and all the elements are equal, then the matrices are equal.
}

// write matrix to an output stream with the specified field width
template <typename ElemType>
void MatrixAlgebra::MatrixBase<ElemType>::output(std::ostream& out, int fieldWidth)
{
    for (unsigned row = 0U; row < this->numOfRows; row++)
    {
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            out << std::setw(fieldWidth) << (*this)[row][col] << ' ';
        out << std::endl;
    }
}

// A convenient operator overload to compare two matrix objects for equality.
template <typename ElemType>
bool MatrixAlgebra::MatrixBase<ElemType>::operator==(const MatrixAlgebra::MatrixBase<ElemType>& matrix)
{
    return this->equal(matrix);
}

// Overload operator!= to compare two matricies for negated equality
template <typename ElemType>
bool MatrixAlgebra::MatrixBase<ElemType>::operator!=(const MatrixAlgebra::MatrixBase<ElemType>& matrix)
{
    return !(*this == matrix);
}

// Overload operator= to allow copying the contents of one matrix to another.
template <typename ElemType>
MatrixAlgebra::MatrixBase<ElemType>& MatrixAlgebra::MatrixBase<ElemType>::operator=(const MatrixAlgebra::MatrixBase<ElemType>& matrix2)
{
    unsigned matrix2NumOfRows       =   matrix2.getNumOfRows();
    unsigned matrix2NumOfColumns    =   matrix2.getNumOfColumns();

    if (matrix2NumOfColumns > this->numOfColumns && matrix2NumOfRows > this->numOfRows)
    {
        for (unsigned row = 0; row < this->numOfRows; row++)
            for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                if (col < this->numOfColumns)
                    (*this)[row][col] = matrix2[row][col];
                else
                    (*this)[row].push_back(matrix2[row][col]);

        std::vector<ElemType> temp;
        for (unsigned i = 0; i < matrix2NumOfColumns; i++)
            temp.push_back(0);
        for (unsigned j = this->numOfRows; j < matrix2NumOfRows; j++)
            this->data.push_back(temp);

        for (unsigned row = this->numOfRows; row < matrix2NumOfRows; row++)
            for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                (*this)[row][col] = matrix2[row][col];

        this->numOfRows     =   matrix2NumOfRows;    // "this" now the same number of rows and columns as "matrix2"
        this->numOfColumns  =   matrix2NumOfColumns; //
    }
    else if (matrix2NumOfColumns > this->numOfColumns && matrix2NumOfRows <= this->numOfRows)
    {
        for (unsigned row = 0; row < matrix2NumOfRows; row++)
            for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                if (col < this->numOfColumns)
                    (*this)[row][col] = matrix2[row][col];
                else
                    (*this)[row].push_back(matrix2[row][col]);

        for (unsigned row = matrix2NumOfRows; row < this->numOfRows; row++)
            for (unsigned i = this->numOfColumns; i < matrix2NumOfColumns; i++)
                (*this)[row].push_back(0);

        this->numOfColumns = matrix2NumOfColumns; // "this" now has the same number of columns as "matrix2"
    }
    else if (matrix2NumOfRows > this->numOfRows && matrix2NumOfColumns <= this->numOfColumns)
    {
        std::vector<ElemType> temp;
        for (unsigned i = 0; i < this->numOfColumns; i++)
            temp.push_back(0);
        for (unsigned i = this->numOfRows; i < matrix2NumOfRows; i++)
            this->data.push_back(temp);

        for (unsigned row = 0; row < matrix2NumOfRows; row++)
            for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                (*this)[row][col] = matrix2[row][col];

        this->numOfRows = matrix2NumOfRows; // "this" now has the same number of Rows as "matrix2"
    }
    else // "matrix2" has less than or equal to the number of rows and columns as "this".
    {
        for (unsigned row = 0; row < matrix2NumOfRows; row++)
            for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                (*this)[row][col] = matrix2[row][col];
    }

    return *this;
}

// Overload operator[] to allow indexing of a matrix like this MatrixBaseInstance[row][col]
template <typename ElemType>
std::vector<ElemType>& MatrixAlgebra::MatrixBase<ElemType>::operator[](std::size_t row) { return this->data[row]; }

// Overload operator[] to allow read-only indexing of a matrix
template <typename ElemType>
const std::vector<ElemType>& MatrixAlgebra::MatrixBase<ElemType>::operator[](std::size_t row) const { return this->data[row]; }

// Return the number of rows in the matrix.
template <typename ElemType>
unsigned MatrixAlgebra::MatrixBase<ElemType>::getNumOfRows() const { return this->numOfRows; }

// Return the number of columns in the matrix.
template <typename ElemType>
unsigned MatrixAlgebra::MatrixBase<ElemType>::getNumOfColumns() const { return this->numOfColumns; }

// Returns a Boolean value indicating whether or not a matrix is square. A matrix is considered square if the number of rows equals the number of columns.
template <typename ElemType>
bool MatrixAlgebra::MatrixBase<ElemType>::isSquare() { return this->numOfColumns == this->numOfRows; }

// checks if all of the elements of the matrix have the specified value
template <typename ElemType>
bool MatrixAlgebra::MatrixBase<ElemType>::allElementsAre(ElemType val)
{
    double doubleVal = static_cast<double>(val);

    for (unsigned row = 0U; row < this->numOfRows; row++)
        for (unsigned col = 0U; col < this->numOfColumns; col++)
            if (!MatrixAlgebra::isCloseEnough(doubleVal, static_cast<double>((*this)[row][col]), 0.0000001))
                return false;
    
    return true;
}

template class MatrixAlgebra::MatrixBase<int>;
template class MatrixAlgebra::MatrixBase<double>;
template class MatrixAlgebra::MatrixBase<unsigned>;
template class MatrixAlgebra::MatrixBase<float>;

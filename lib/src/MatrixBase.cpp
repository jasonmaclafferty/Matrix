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

template <typename ElemType>
void MatrixBase<ElemType>::setElement(unsigned row, unsigned col, ElemType newElemVal)
{
    if (row < this->getNumOfRows() && col < this->getNumOfColumns())
        this->data[row][col] = newElemVal;
}

template <typename ElemType>
ElemType MatrixBase<ElemType>::getElement(unsigned row, unsigned col) const
{
    ElemType retval;
    if (row < this->getNumOfRows() && col < this->getNumOfColumns())
        retval = this->data[row][col];

    return retval;
}

template <typename ElemType>
MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns)
{
    this->init(numberOfRows, numberOfColumns, 0);
}

template <typename ElemType>
MatrixBase<ElemType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal) 
{ 
    this->init(numberOfRows, numberOfColumns, elemInitVal); 
}

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

template <typename ElemType>
bool MatrixBase<ElemType>::isIdentity()
{

    return true; // stub--implement later
}

template <typename ElemType>
bool MatrixBase<ElemType>::isZero()
{

    return true; // stub--implement later
}

template <typename ElemType>
bool MatrixBase<ElemType>::equal(const MatrixBase<ElemType>& matrix) const
{
    if (this->getNumOfRows() == matrix.getNumOfRows() && this->getNumOfColumns() == matrix.getNumOfColumns())
    {
        for (unsigned row = 0U; row < this->getNumOfRows(); row++)
            for (unsigned col = 0U; col < this->getNumOfColumns(); col++)
                if (this->getElement(row, col) != matrix.getElement(row, col))
                    return false; // matrices are not equal because one of the pairs of matrix elements are not equal
    }
    else
    {
        return false; // matrices are not equal because the dimensions are not equal
    }

    return true; // if the dimensions match and all the elements are equal, then the matrices are equal
}

template <typename ElemType>
std::ostream& operator<<(std::ostream& out, const MatrixBase<ElemType>& matrix)
{

    return out; // stub to implement later
}

template <typename ElemType>
bool operator==(const MatrixBase<ElemType>& matrix1, const MatrixBase<ElemType>& matrix2)
{

    return true;// stub to implement later
}

template <typename ElemType>
MatrixBase<ElemType>& MatrixBase<ElemType>::operator=(const MatrixBase<ElemType>& matrix2)
{

    return *this; // stub to implement later
}

template <typename ElemType>
unsigned MatrixBase<ElemType>::getNumOfRows() const { return this->numOfRows; }

template <typename ElemType>
unsigned MatrixBase<ElemType>::getNumOfColumns() const { return this->numOfColumns; }

template <typename ElemType>
bool MatrixBase<ElemType>::isSquare() { return this->numOfColumns == this->numOfRows; }

template class MatrixBase<int>;
template class MatrixBase<double>;
template class MatrixBase<unsigned>;
template class MatrixBase<float>;

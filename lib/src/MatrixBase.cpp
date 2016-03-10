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

namespace MatrixAlgebra
{
    template <typename ElemType>
    MatrixBase<ElemType>::MatrixBase(const MatrixBase<ElemType>& matrixToCopyFrom)
    {
        this->numOfRows     =   matrixToCopyFrom.getNumOfRows();
        this->numOfColumns  =   matrixToCopyFrom.getNumOfColumns();
        std::vector<ElemType> temp;
        for (unsigned i = 0; i < numOfColumns; i++)
        {
            temp.push_back(0);
        }
        for (unsigned row = 0; row < this->numOfRows; row++)
        {
            this->data.push_back(temp);
        }
        for (unsigned row = 0; row < this->numOfRows; row++)
        {
            for (unsigned col = 0; col < this->numOfColumns; col++)
            {
                (*this)[row][col] = matrixToCopyFrom[row][col];
            }
        }
    }

    template <typename ElemType>
    void MatrixBase<ElemType>::setElement(unsigned row, unsigned col, ElemType newElemVal)
    {
        if (row < this->numOfRows && col < this->numOfColumns)
        {
            this->data[row][col] = newElemVal;
        }
    }

    template <typename ElemType>
    ElemType MatrixBase<ElemType>::getElement(unsigned row, unsigned col) const
    {
        ElemType retval;
        if (row < this->numOfRows && col < this->numOfColumns)
        {
            retval = this->data[row][col];
        }

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
        {
            temp.push_back(elemInitVal);
        }

        for (unsigned i = 0; i < numberOfRows; i++)
        {
            this->data.push_back(temp);
        }
    }

    template <typename ElemType>
    bool MatrixBase<ElemType>::isIdentity()
    {
        if (this->numOfRows == this->numOfColumns)
        {
            for (unsigned row = 0U; row < this->numOfRows; row++)
            {
                if (!isCloseEnough(static_cast<double>(this->getElement(row, row)), 1, 0.000001))
                {
                    return false;
                }
            }
        }
        else
        {
            return false; // numOfRows != numOfColumns = !identity
        }

        return true; // The matrix is the identity matrix. 
    }

    template <typename ElemType>
    bool MatrixBase<ElemType>::isZero()
    {
        for (unsigned row = 0U; row < this->numOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numOfColumns; col++)
            {
                if (!isCloseEnough(this->getElement(row, col), 0, 0.000001))
                {
                    return false; // A non-zero value was found. So, the matrix does not constitute the zero matrix.
                }
            }
        }

        return true; // All of the matrix elements are 0.
    }

    template <typename ElemType>
    bool MatrixBase<ElemType>::equal(const MatrixBase<ElemType>& matrix) const
    {
        if (this->numOfRows == matrix.getNumOfRows() && this->numOfColumns == matrix.getNumOfColumns())
        {
            for (unsigned row = 0U; row < this->numOfRows; row++)
            {
                for (unsigned col = 0U; col < this->numOfColumns; col++)
                {
                    if (!isCloseEnough(static_cast<double>(this->getElement(row, col)), static_cast<double>(matrix[row][col]), 0.000000000001))
                    {
                        return false; // Matrices are not equal because one of the pairs of matrix elements are not equal.
                    }
                }
            }
        }
        else
        {
            return false; // Matrices are not equal because the dimensions are not equal.
        }

        return true; // If the dimensions match and all the elements are equal, then the matrices are equal.
    }

    template <typename ElemType>
    void MatrixBase<ElemType>::output(std::ostream& out, int fieldWidth)
    {
        for (unsigned row = 0U; row < this->numOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numOfColumns; col++)
            {
                out << std::setw(fieldWidth) << (*this)[row][col] << ' ';
            }
            out << std::endl;
        }
    }

    template <typename ElemType>
    bool MatrixBase<ElemType>::operator==(const MatrixBase<ElemType>& matrix)
    {
        return this->equal(matrix);
    }

    template <typename ElemType>
    bool MatrixBase<ElemType>::operator!=(const MatrixBase<ElemType>& matrix)
    {
        return !(*this == matrix);
    }

    template <typename ElemType>
    MatrixBase<ElemType>& MatrixBase<ElemType>::operator=(const MatrixBase<ElemType>& matrix2)
    {
        unsigned matrix2NumOfRows       =   matrix2.getNumOfRows();
        unsigned matrix2NumOfColumns    =   matrix2.getNumOfColumns();

        if (matrix2NumOfColumns > this->numOfColumns && matrix2NumOfRows > this->numOfRows)
        {
            for (unsigned row = 0; row < this->numOfRows; row++)
            {
                for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                {
                    if (col < this->numOfColumns)
                    {
                        (*this)[row][col] = matrix2[row][col];
                    }
                    else
                    {
                        (*this)[row].push_back(matrix2[row][col]);
                    }
                }
            }

            std::vector<ElemType> temp;
            for (unsigned i = 0; i < matrix2NumOfColumns; i++)
            {
                temp.push_back(0);
            }
            for (unsigned j = this->numOfRows; j < matrix2NumOfRows; j++)
            {
                this->data.push_back(temp);
            }
            for (unsigned row = this->numOfRows; row < matrix2NumOfRows; row++)
            {
                for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                {
                    (*this)[row][col] = matrix2[row][col];
                }
            }

            this->numOfRows     =   matrix2NumOfRows;    // "this" now the same number of rows and columns as "matrix2"
            this->numOfColumns  =   matrix2NumOfColumns; //
        }
        else if (matrix2NumOfColumns > this->numOfColumns && matrix2NumOfRows <= this->numOfRows)
        {
            for (unsigned row = 0; row < matrix2NumOfRows; row++)
            {
                for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                {
                    if (col < this->numOfColumns)
                    {
                        (*this)[row][col] = matrix2[row][col];
                    }
                    else
                    {
                        (*this)[row].push_back(matrix2[row][col]);
                    }
                }
            }

            for (unsigned row = matrix2NumOfRows; row < this->numOfRows; row++)
            {
                for (unsigned i = this->numOfColumns; i < matrix2NumOfColumns; i++)
                {
                    (*this)[row].push_back(0);
                }
            }

            this->numOfColumns = matrix2NumOfColumns; // "this" now has the same number of columns as "matrix2"
        }
        else if (matrix2NumOfRows > this->numOfRows && matrix2NumOfColumns <= this->numOfColumns)
        {
            std::vector<ElemType> temp;
            for (unsigned i = 0; i < this->numOfColumns; i++)
            {
                temp.push_back(0);
            }
            for (unsigned i = this->numOfRows; i < matrix2NumOfRows; i++)
            {
                this->data.push_back(temp);
            }

            for (unsigned row = 0; row < matrix2NumOfRows; row++)
            {
                for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                {
                    (*this)[row][col] = matrix2[row][col];
                }
            }

            this->numOfRows = matrix2NumOfRows; // "this" now has the same number of Rows as "matrix2"
        }
        else // "matrix2" has less than or equal to the number of rows and columns as "this".
        {
            for (unsigned row = 0; row < matrix2NumOfRows; row++)
            {
                for (unsigned col = 0; col < matrix2NumOfColumns; col++)
                {
                    (*this)[row][col] = matrix2[row][col];
                }
            }
        }

        return *this;
    }

    template <typename ElemType>
    std::vector<ElemType>& MatrixBase<ElemType>::operator[](std::size_t row) { return this->data[row]; }

    template <typename ElemType>
    const std::vector<ElemType>& MatrixBase<ElemType>::operator[](std::size_t row) const { return this->data[row]; }

    template <typename ElemType>
    unsigned MatrixBase<ElemType>::getNumOfRows() const { return this->numOfRows; }

    template <typename ElemType>
    unsigned MatrixBase<ElemType>::getNumOfColumns() const { return this->numOfColumns; }

    template <typename ElemType>
    bool MatrixBase<ElemType>::isSquare() { return this->numOfColumns == this->numOfRows; }

    template <typename ElemType>
    bool MatrixBase<ElemType>::allElementsAre(ElemType val)
    {
        double doubleVal = static_cast<double>(val);

        for (unsigned row = 0U; row < this->numOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numOfColumns; col++)
            {
                if (!isCloseEnough(doubleVal, static_cast<double>((*this)[row][col]), 0.0000001))
                {
                    return false;
                }
            }
        }
        
        return true;
    }

template class MatrixBase<int>;
template class MatrixBase<double>;
template class MatrixBase<unsigned>;
template class MatrixBase<float>;
template class MatrixBase<long>;
template class MatrixBase<long long>;
template class MatrixBase<long double>;
template class MatrixBase<unsigned long>;
}

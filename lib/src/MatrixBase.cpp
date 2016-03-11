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
    template <typename ElementType>
    MatrixBase<ElementType>::MatrixBase(const MatrixBase<ElementType>& matrixToCopyFrom)
    {
        this->numberOfRows     =   matrixToCopyFrom.getNumberOfRows();
        this->numberOfColumns  =   matrixToCopyFrom.getNumberOfColumns();
        std::vector<ElementType> temp;
        for (unsigned i = 0; i < numberOfColumns; i++)
        {
            temp.push_back(0);
        }
        for (unsigned row = 0; row < this->numberOfRows; row++)
        {
            this->data.push_back(temp);
        }
        for (unsigned row = 0; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0; col < this->numberOfColumns; col++)
            {
                (*this)[row][col] = matrixToCopyFrom[row][col];
            }
        }
    }

    template <typename ElementType>
    void MatrixBase<ElementType>::setElement(unsigned row, unsigned column, ElementType newElemVal)
    {
        if (row < this->numberOfRows && column < this->numberOfColumns)
        {
            this->data[row][column] = newElemVal;
        }
    }

    template <typename ElementType>
    ElementType MatrixBase<ElementType>::getElement(unsigned row, unsigned column) const
    {
        ElementType retval;
        if (row < this->numberOfRows && column < this->numberOfColumns)
        {
            retval = this->data[row][column];
        }

        return retval;
    }

    template <typename ElementType>
    MatrixBase<ElementType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns)
    {
        this->init(numberOfRows, numberOfColumns, 0);
    }

    template <typename ElementType>
    MatrixBase<ElementType>::MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElementType elementInitializationValue) 
    { 
        this->init(numberOfRows, numberOfColumns, elementInitializationValue); 
    }

    template <typename ElementType>
    void MatrixBase<ElementType>::init(unsigned numberOfRows, unsigned numberOfColumns, ElementType elementInitializationValue)
    {
        this->numberOfRows     =   numberOfRows;
        this->numberOfColumns  =   numberOfColumns;
        std::vector<ElementType> temp;

        for (unsigned i = 0; i < numberOfColumns; i++)
        {
            temp.push_back(elementInitializationValue);
        }

        for (unsigned i = 0; i < numberOfRows; i++)
        {
            this->data.push_back(temp);
        }
    }

    template <typename ElementType>
    bool MatrixBase<ElementType>::isIdentity()
    {
        if (this->numberOfRows == this->numberOfColumns)
        {
            for (unsigned row = 0U; row < this->numberOfRows; row++)
            {
                if (!isCloseEnough(static_cast<double>(this->getElement(row, row)), 1, 0.000001))
                {
                    return false;
                }
            }
        }
        else
        {
            return false; // numberOfRows != numberOfColumns = !identity
        }

        return true; // The matrix is the identity matrix. 
    }

    template <typename ElementType>
    bool MatrixBase<ElementType>::isZero()
    {
        for (unsigned row = 0U; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numberOfColumns; col++)
            {
                if (!isCloseEnough(this->getElement(row, col), 0, 0.000001))
                {
                    return false; // A non-zero value was found. So, the matrix does not constitute the zero matrix.
                }
            }
        }

        return true; // All of the matrix elements are 0.
    }

    template <typename ElementType>
    bool MatrixBase<ElementType>::equal(const MatrixBase<ElementType>& matrix) const
    {
        if (this->numberOfRows == matrix.getNumberOfRows() && this->numberOfColumns == matrix.getNumberOfColumns())
        {
            for (unsigned row = 0U; row < this->numberOfRows; row++)
            {
                for (unsigned col = 0U; col < this->numberOfColumns; col++)
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

    template <typename ElementType>
    void MatrixBase<ElementType>::output(std::ostream& out, int fieldWidth)
    {
        for (unsigned row = 0U; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numberOfColumns; col++)
            {
                out << std::setw(fieldWidth) << (*this)[row][col] << ' ';
            }
            out << std::endl;
        }
    }

    template <typename ElementType>
    bool MatrixBase<ElementType>::operator==(const MatrixBase<ElementType>& matrix)
    {
        return this->equal(matrix);
    }

    template <typename ElementType>
    bool MatrixBase<ElementType>::operator!=(const MatrixBase<ElementType>& matrix)
    {
        return !(*this == matrix);
    }

    template <typename ElementType>
    MatrixBase<ElementType>& MatrixBase<ElementType>::operator=(const MatrixBase<ElementType>& otherMatrix)
    {
        unsigned otherMatrixNumOfRows       =   otherMatrix.getNumberOfRows();
        unsigned otherMatrixNumOfColumns    =   otherMatrix.getNumberOfColumns();

        if (otherMatrixNumOfColumns > this->numberOfColumns && otherMatrixNumOfRows > this->numberOfRows)
        {
            for (unsigned row = 0; row < this->numberOfRows; row++)
            {
                for (unsigned col = 0; col < otherMatrixNumOfColumns; col++)
                {
                    if (col < this->numberOfColumns)
                    {
                        (*this)[row][col] = otherMatrix[row][col];
                    }
                    else
                    {
                        (*this)[row].push_back(otherMatrix[row][col]);
                    }
                }
            }

            std::vector<ElementType> temp;
            for (unsigned i = 0; i < otherMatrixNumOfColumns; i++)
            {
                temp.push_back(0);
            }
            for (unsigned j = this->numberOfRows; j < otherMatrixNumOfRows; j++)
            {
                this->data.push_back(temp);
            }
            for (unsigned row = this->numberOfRows; row < otherMatrixNumOfRows; row++)
            {
                for (unsigned col = 0; col < otherMatrixNumOfColumns; col++)
                {
                    (*this)[row][col] = otherMatrix[row][col];
                }
            }

            this->numberOfRows     =   otherMatrixNumOfRows;    // "this" now the same number of rows and columns as "otherMatrix"
            this->numberOfColumns  =   otherMatrixNumOfColumns; //
        }
        else if (otherMatrixNumOfColumns > this->numberOfColumns && otherMatrixNumOfRows <= this->numberOfRows)
        {
            for (unsigned row = 0; row < otherMatrixNumOfRows; row++)
            {
                for (unsigned col = 0; col < otherMatrixNumOfColumns; col++)
                {
                    if (col < this->numberOfColumns)
                    {
                        (*this)[row][col] = otherMatrix[row][col];
                    }
                    else
                    {
                        (*this)[row].push_back(otherMatrix[row][col]);
                    }
                }
            }

            for (unsigned row = otherMatrixNumOfRows; row < this->numberOfRows; row++)
            {
                for (unsigned i = this->numberOfColumns; i < otherMatrixNumOfColumns; i++)
                {
                    (*this)[row].push_back(0);
                }
            }

            this->numberOfColumns = otherMatrixNumOfColumns; // "this" now has the same number of columns as "otherMatrix"
        }
        else if (otherMatrixNumOfRows > this->numberOfRows && otherMatrixNumOfColumns <= this->numberOfColumns)
        {
            std::vector<ElementType> temp;
            for (unsigned i = 0; i < this->numberOfColumns; i++)
            {
                temp.push_back(0);
            }
            for (unsigned i = this->numberOfRows; i < otherMatrixNumOfRows; i++)
            {
                this->data.push_back(temp);
            }

            for (unsigned row = 0; row < otherMatrixNumOfRows; row++)
            {
                for (unsigned col = 0; col < otherMatrixNumOfColumns; col++)
                {
                    (*this)[row][col] = otherMatrix[row][col];
                }
            }

            this->numberOfRows = otherMatrixNumOfRows; // "this" now has the same number of Rows as "otherMatrix"
        }
        else // "otherMatrix" has less than or equal to the number of rows and columns as "this".
        {
            for (unsigned row = 0; row < otherMatrixNumOfRows; row++)
            {
                for (unsigned col = 0; col < otherMatrixNumOfColumns; col++)
                {
                    (*this)[row][col] = otherMatrix[row][col];
                }
            }
        }

        return *this;
    }

    template <typename ElementType>
    std::vector<ElementType>& MatrixBase<ElementType>::operator[](std::size_t row) { return this->data[row]; }

    template <typename ElementType>
    const std::vector<ElementType>& MatrixBase<ElementType>::operator[](std::size_t row) const { return this->data[row]; }

    template <typename ElementType>
    unsigned MatrixBase<ElementType>::getNumberOfRows() const { return this->numberOfRows; }

    template <typename ElementType>
    unsigned MatrixBase<ElementType>::getNumberOfColumns() const { return this->numberOfColumns; }

    template <typename ElementType>
    bool MatrixBase<ElementType>::isSquare() { return this->numberOfColumns == this->numberOfRows; }

    template <typename ElementType>
    bool MatrixBase<ElementType>::allElementsAre(ElementType val)
    {
        double doubleVal = static_cast<double>(val);

        for (unsigned row = 0U; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numberOfColumns; col++)
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

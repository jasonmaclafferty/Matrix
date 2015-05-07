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

#ifndef _MATRIXBASE_HPP_
#define _MATRIXBASE_HPP_

#include <ostream>
#include <vector>

template <typename ElemType>
class MatrixBase
{
    protected:
        std::vector< std::vector<ElemType> > data;

        unsigned numOfRows, numOfColumns;

    public:
        MatrixBase(unsigned numberOfRows, unsigned numberOfColumns);

        MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal);

        bool isIdentity();

        bool isZero();

        inline bool isSquare() { return this->numOfRows == this->numOfColumns; }

        inline ElemType getElement(unsigned row, unsigned col) const { return this->data[row][col]; } 

        void setElement(unsigned row, unsigned col, ElemType newElemVal) { this->data[row][col] = newElemVal; }

        bool equal(const MatrixBase<ElemType>& matrix) const;

        bool operator==(const MatrixBase<ElemType>& matrix2);

        MatrixBase<ElemType>& operator=(const MatrixBase<ElemType>& matrix2);

        inline unsigned getNumOfRows() const { return this->numOfRows; }

        inline unsigned getNumOfColumns() const { return this->numOfColumns; }
};

template <typename ElemType>
std::ostream& operator<<(std::ostream& out, const MatrixBase<ElemType>& matrix);

#endif

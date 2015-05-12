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

        void init(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal);

    public:
        MatrixBase(unsigned numberOfRows, unsigned numberOfColumns);

        MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal);

        bool isIdentity();

        bool isZero();

        bool isSquare();

        ElemType getElement(unsigned row, unsigned col) const; 

        void setElement(unsigned row, unsigned col, ElemType newElemVal);

        bool equal(const MatrixBase<ElemType>& matrix) const;

        MatrixBase<ElemType>& operator=(const MatrixBase<ElemType>& matrix);

        unsigned getNumOfRows() const;

        unsigned getNumOfColumns() const;
        
        bool operator==(const MatrixBase<ElemType>& matrix);

        bool operator!=(const MatrixBase<ElemType>& matrix);

        std::vector<ElemType>& operator[](std::size_t row);

        const std::vector<ElemType>& operator[](std::size_t row) const;
};

template <typename ElemType>
std::ostream& operator<<(std::ostream& out, const MatrixBase<ElemType>& matrix);

#endif

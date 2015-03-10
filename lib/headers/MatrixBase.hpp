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

namespace MatrixAlgebra
{
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

            inline bool isSquare();

            inline ElemType getElement(unsigned row, unsigned col);

            void setElement(unsigned row, unsigned col, ElemType newElemVal);

            bool equal(const MatrixBase& matrix);

            std::ostream& operator<<(std::ostream& out, const MatrixBase& matrix);

            bool& operator==(const MatrixBase& matrix1, const MatrixBase& matrix2);

            MatrixBase& operator=(MatrixBase& matrix1, const MatrixBase& matrix2);

            unsigned getNumOfRows();

            unsigned getNumOfColumns();
    }
}

#endif

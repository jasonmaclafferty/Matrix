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
#include <iomanip>

namespace MatrixAlgebra
{
    template <typename ElemType>
    class MatrixBase
    {
        protected:
            std::vector< std::vector<ElemType> > data;

            unsigned numOfRows, numOfColumns;

            // Initialization function which does all of the heavy lifting for the MatrixBase class constructors.
            void init(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal);

        public:
            // MatrixBase class constructor accepting parameters specified the desired number of rows and columns for the matrix.
            MatrixBase(unsigned numberOfRows, unsigned numberOfColumns);

            // MatrixBase class constructor accepting as arguments the desired number of rows and columns .
            // for the matrix to be created along with what value each matrix element should have.
            MatrixBase(unsigned numberOfRows, unsigned numberOfColumns, ElemType elemInitVal);

            // Copy Constructor
            MatrixBase(const MatrixBase<ElemType>& matrixToCopyFrom);

            // Returns a Boolean value indicating whether or not the matrix is the identity matrix.
            // An identity matrix is defined to have the value of 1 for all the elements along the matrix diagonal and 0's everywhere else.
            // Additionally, all identity matricies are square--that is the number of rows = the number of columns.
            // For matricies containing float or double values, an identity matrix is guaranteed to have values along the diagonal equal to 1 +/- 0.000001.
            // Matricies of int or unsigned values are guaranteed to have values of exactly 1 along the diagonal if they are identity matricies.
            bool isIdentity();

            // Returns a Boolean value indicating whether or not the matrix is the Zero Matrix.
            // The Zero Matrix is defined a matrix containing all zero values for all of its elements.
            // For matricies of int or unsigned values, zero matricies are guaranteed to have all elements with a value of exactly 0.
            // For matricies of double or float values, all elements are guaranteed to have values of 0 +/- 0.000001
            bool isZero();

            // Returns a Boolean value indicating whether or not a matrix is square. A matrix is considered square if 
            // the number of rows equals the number of columns.
            bool isSquare();

            // Returns the matrix element at position "row", "col" if  given a valid row, col position--otherwise the return value is unspecified.
            virtual ElemType getElement(unsigned row, unsigned col) const; 

            // Assigns the value "newElemVal" to the matrix element at position "row", "col" if a valid row and column are given--otherwise nothing is done.
            virtual void setElement(unsigned row, unsigned col, ElemType newElemVal);

            // write matrix to an output stream with the specified field width
            virtual void output(std::ostream& out, int fieldWidth);

            // checks if all of the elements of the matrix have the specified value
            virtual bool allElementsAre(ElemType val);

            // Returns the Boolean result of comparing two matricies for equality. Two matrices are considered equal if they have the same dimensions
            // and all of their corresponding elements are equal.
            // If matricies of int or unsigned values are equal, then their corresponding values are guaranteed to be exactly equal.
            // Otherwise, if the matricies contain values of type double or float, then corresponding values will be within +/- 0.000001 
            // of each other for equal matricies.
            virtual bool equal(const MatrixBase<ElemType>& matrix) const;

            // Return the number of rows in the matrix.
            unsigned getNumOfRows() const;

            // Return the number of columns in the matrix.
            unsigned getNumOfColumns() const;
            
            // A convenient operator overload to compare two matrix objects for equality.
            virtual bool operator==(const MatrixBase<ElemType>& matrix);

            // Overload operator= to allow copying the contents of one matrix to another.
            virtual MatrixBase<ElemType>& operator=(const MatrixBase<ElemType>& matrix);

            // Overload operator!= to compare two matricies for negated equality
            virtual bool operator!=(const MatrixBase<ElemType>& matrix);

            // Overload operator[] to allow indexing of a matrix like this MatrixBaseInstance[row][col]
            virtual std::vector<ElemType>& operator[](std::size_t row);

            // Overload operator[] to allow read-only indexing of a matrix
            virtual const std::vector<ElemType>& operator[](std::size_t row) const;

    };

    // Overload for operator<< to allow writing a matrix to an output stream such as a file or the console.
    template <typename ElemType>
    std::ostream& operator<<(std::ostream& out, const MatrixBase<ElemType>& matrix)
    {
        unsigned matrixNumberOfColumns  =   matrix.getNumOfColumns();
        unsigned matrixNumberOfRows     =   matrix.getNumOfRows();
        for (unsigned row = 0U; row < matrixNumberOfRows; row++)
        {
            for (unsigned col = 0U; col < matrixNumberOfColumns; col++)
            {
                out << std::setw(15) << matrix[row][col] << ' ';
            }
            out << std::endl;
        }

        return out; 
    }
}

#endif

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

namespace MatrixAlgebra
{
    template <typename ElementType>
    void Matrix<ElementType>::power(double exponent)
    {
        for (unsigned row = 0U; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numberOfColumns; col++)
            {
                (*this)[row][col] = static_cast<ElementType>(pow(static_cast<double>((*this)[row][col]), exponent));
            }
        }
    }

    template <typename ElementType>
    void Matrix<ElementType>::add(const Matrix<ElementType>& otherMatrix){ this->addRange(otherMatrix, 0, this->numberOfColumns - 1U); }

    template <typename ElementType>
    void Matrix<ElementType>::subtract(const Matrix<ElementType>& otherMatrix){ this->subtractRange(otherMatrix, 0, this->numberOfColumns - 1U); }

    template <typename ElementType>
    void Matrix<ElementType>::multiplyRange(unsigned thisRowStart, unsigned thisRowEnd, const Matrix<ElementType>& otherMatrix, 
                                         unsigned otherMatrixColStart, unsigned otherMatrixColEnd, Matrix<ElementType>& out)
    {
        if (out.getNumberOfRows() == this->numberOfRows && out.getNumberOfColumns() == otherMatrix.getNumberOfColumns())
        {
            if (thisRowEnd < this->numberOfRows && otherMatrixColEnd < otherMatrix.getNumberOfColumns())
            {
                if (this->numberOfColumns == otherMatrix.getNumberOfRows())
                {
                    for (unsigned outRow = thisRowStart; outRow <= thisRowEnd; outRow++)
                    {
                        for (unsigned outCol = otherMatrixColStart; outCol <= otherMatrixColEnd; outCol++)
                        {
                            for (unsigned productCtr = 0; productCtr < this->numberOfColumns; productCtr++)
                            {
                                if (productCtr == 0)
                                {
                                    out[outRow][outCol] = (*this)[outRow][productCtr] * otherMatrix[productCtr][outCol];
                                }
                                else
                                {
                                    out[outRow][outCol] += (*this)[outRow][productCtr] * otherMatrix[productCtr][outCol];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    template <typename ElementType>
    std::shared_ptr< Matrix<ElementType> > Matrix<ElementType>::multiply(const Matrix<ElementType>& otherMatrix)
    {
        std::shared_ptr< Matrix<ElementType> > retval = std::make_shared< Matrix<ElementType> >(this->numberOfColumns, otherMatrix.getNumberOfColumns());
        this->multiplyRange(0, this->numberOfColumns - 1U, otherMatrix, 0, otherMatrix.getNumberOfColumns() - 1U, *retval);

        return retval;
    }

    template <typename ElementType>
    void Matrix<ElementType>::addRange(const Matrix<ElementType>& otherMatrix, unsigned rowStart, unsigned rowEnd)
    {
        if (this->numberOfColumns == otherMatrix.getNumberOfColumns() && this->numberOfRows == otherMatrix.getNumberOfRows())
        {
            if (rowEnd < this->numberOfRows)
            {
                for (unsigned row = rowStart; row <= rowEnd; row++)
                {
                    for (unsigned col = 0U; col < this->numberOfColumns; col++)
                    {
                        (*this)[row][col] += otherMatrix[row][col];   
                    }
                }
            }
        }
    }

    template <typename ElementType>
    void Matrix<ElementType>::subtractRange(const Matrix<ElementType>& otherMatrix, unsigned rowStart, unsigned rowEnd)
    {
        if (this->numberOfColumns == otherMatrix.getNumberOfColumns() && this->numberOfRows == otherMatrix.getNumberOfRows())
        {
            if (rowEnd < this->numberOfRows)
            {
                for (unsigned row = rowStart; row <= rowEnd; row++)
                {
                    for (unsigned col = 0U; col < this->numberOfColumns; col++)
                    {
                        (*this)[row][col] -= otherMatrix[row][col];   
                    }
                }
            }
        }
    }

    template <typename ElementType>
    void Matrix<ElementType>::scale(ElementType scaleFactor)
    {
        for (unsigned row = 0U; row < this->numberOfRows; row++)
        {
            for (unsigned col = 0U; col < this->numberOfColumns; col++)
            {
                (*this)[row][col] *= scaleFactor;
            }
        }
    }

    template <typename ElementType>
    Matrix<ElementType>& Matrix<ElementType>::operator=(Matrix<ElementType>& otherMatrix)
    {
        MatrixBase<ElementType>& otherMatrixTemp    =  otherMatrix; 
        MatrixBase<ElementType>& thisTemp           =  *this; 
        thisTemp                                    =   otherMatrixTemp;

        return dynamic_cast< Matrix<ElementType>& >(thisTemp);
    }

    template <typename ElementType>
    std::shared_ptr< Matrix<ElementType> > Matrix<ElementType>::operator+(const Matrix<ElementType>& otherMatrix)
    {
        unsigned otherMatrixNumOfRows = otherMatrix.getNumberOfRows(), otherMatrixNumOfColumns = otherMatrix.getNumberOfColumns();
        std::shared_ptr< Matrix<ElementType> > retval = std::make_shared< Matrix<ElementType> >(otherMatrixNumOfRows, otherMatrixNumOfColumns);

        if (this->numberOfRows == otherMatrixNumOfRows && this->numberOfColumns == otherMatrixNumOfColumns)
        {
            for (unsigned row = 0U; row < this->numberOfRows; row++)
            {
                for (unsigned col = 0U; col < this->numberOfColumns; col++)
                {
                    (*retval)[row][col] = (*this)[row][col] + otherMatrix[row][col];
                }
            }
        }

        return retval;
    }

    template <typename ElementType>
    std::shared_ptr< Matrix<ElementType> > Matrix<ElementType>::operator-(const Matrix<ElementType>& otherMatrix)
    {
        unsigned otherMatrixNumOfRows = otherMatrix.getNumberOfRows(), otherMatrixNumOfColumns = otherMatrix.getNumberOfColumns();
        std::shared_ptr< Matrix<ElementType> > retval = std::make_shared< Matrix<ElementType> >(otherMatrixNumOfRows, otherMatrixNumOfColumns);

        if (this->numberOfRows == otherMatrixNumOfRows && this->numberOfColumns == otherMatrixNumOfColumns)
        {
            for (unsigned row = 0U; row < this->numberOfRows; row++)
            {
                for (unsigned col = 0U; col < this->numberOfColumns; col++)
                {
                    (*retval)[row][col] = (*this)[row][col] - otherMatrix[row][col];
                }
            }
        }

        return retval;

    }

    template <typename ElementType>
    std::shared_ptr< Matrix<ElementType> > Matrix<ElementType>::operator*(const Matrix<ElementType>& otherMatrix)
    {
        unsigned otherMatrixNumOfColumns    =   otherMatrix.getNumberOfColumns();
        auto retval                         =   std::make_shared< Matrix<ElementType> >(this->numberOfColumns, otherMatrix.getNumberOfColumns());
        this->multiplyRange(0, this->numberOfColumns - 1U, otherMatrix, 0, otherMatrixNumOfColumns - 1U, *retval);

        return retval;
    }

    template <typename ElementType>
    void Matrix<ElementType>::parallelAdd(const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads)
    {
        this->parallelAddSubtractHelper(&Matrix<ElementType>::addRange, otherMatrix, numberOfThreads);
    }

    template <typename ElementType>
    void Matrix<ElementType>::parallelSubtract(const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads)
    {
        this->parallelAddSubtractHelper(&Matrix<ElementType>::subtractRange, otherMatrix, numberOfThreads);
    }

    template <typename ElementType>
    void Matrix<ElementType>::parallelAddSubtractHelper(void (Matrix<ElementType>::*func)
                                                                         (const Matrix<ElementType>&, unsigned, unsigned), 
                                                                    const Matrix<ElementType>& otherMatrix, unsigned numberOfThreads)
    {
        unsigned otherMatrixNumOfRows       =   otherMatrix.getNumberOfRows();
        unsigned otherMatrixNumOfColumns    =   otherMatrix.getNumberOfColumns();
        
        if (this->numberOfRows == otherMatrixNumOfRows && this->numberOfColumns == otherMatrixNumOfColumns)
        {
            if (numberOfThreads > 1U)
            {
                std::vector<unsigned> rowsPerThread;
                this->calculateNumberOfRowsPerThread(rowsPerThread, numberOfThreads);

                // spawn threads to do the arithmetic
                unsigned rowStart = 0;
                std::vector< std::shared_ptr<std::thread> > threads;
                for (unsigned threadPos = 0; threadPos < numberOfThreads; threadPos++)
                {
                    threads.push_back(std::make_shared<std::thread>([this, func, threadPos, &otherMatrix, rowStart, &rowsPerThread]()
                    {
                        (this->*func)(otherMatrix, rowStart, rowStart + (rowsPerThread[threadPos] - 1U));
                    }));
                    rowStart += rowsPerThread[threadPos];
                }
                
                // wait for threads to finish computations
                for (auto thread : threads)
                {
                    thread->join();
                }
            }
            else if (numberOfThreads == 1U)
            {
                // If the user specified only one thread for some odd reason, then we will gracefully just do the arithmetic on the main application thread.
                (this->*func)(otherMatrix, 0, this->numberOfColumns - 1U); 
            }
        }
    }

    template <typename ElementType>
    void Matrix<ElementType>::calculateNumberOfRowsPerThread(std::vector<unsigned>& numberOfRowsPerThread, unsigned numberOfThreads)
    {
        for (unsigned i = 0; i < numberOfThreads; i++)
        {
            numberOfRowsPerThread.push_back(0);
        }

        // calculate the exact number of matrix rows to be processed by each thread.
        for (unsigned threadPos = 0; threadPos < numberOfThreads; threadPos++)
        {
            numberOfRowsPerThread[threadPos] = this->numberOfRows / numberOfThreads;
        }

        unsigned numOfRowsLeft  =   this->numberOfRows % numberOfThreads;
        for (unsigned threadPos = 0; numOfRowsLeft > 0; threadPos++)
        {
            numberOfRowsPerThread[threadPos]++;
            numOfRowsLeft--;
        }
    }

    template <typename ElementType>
    void Matrix<ElementType>::parallelMultiply(const Matrix<ElementType>& otherMatrix, Matrix<ElementType>& out, unsigned numberOfThreads)
    {
        unsigned otherMatrixNumOfColumns = otherMatrix.getNumberOfColumns(), otherMatrixNumOfRows = otherMatrix.getNumberOfRows();
        if (this->numberOfColumns == otherMatrixNumOfRows) // check to make sure the inner dimensions of the two matrices match before we try to do any multiplication.
        {
            if (numberOfThreads > 1U) // do not bother with all of the following work if the user only wants to do the multiplication on one thread.
            {
                // initialize vectors to hold the number of rows to be processed by each thread.
                // each element in each vector correspond to threads 0, 1, 2, and 3 etc.
                std::vector<unsigned> numOfRowsPerThread;
                this->calculateNumberOfRowsPerThread(numOfRowsPerThread, numberOfThreads);

                // spawn threads to do the actual arithmetic
                unsigned rowStart = 0;
                std::vector< std::shared_ptr<std::thread> > threads;
                for (unsigned threadPos = 0; threadPos < numberOfThreads; threadPos++)
                {
                    threads.push_back(std::make_shared<std::thread>([this, threadPos, rowStart, &out, &otherMatrix, &numOfRowsPerThread, otherMatrixNumOfColumns]()
                    { 
                        this->multiplyRange(rowStart, rowStart + (numOfRowsPerThread[threadPos] - 1U), otherMatrix, 0, otherMatrixNumOfColumns - 1U, out); 
                    }));
                    rowStart += numOfRowsPerThread[threadPos];
                }

                // wait for threads to finish computations
                for (auto thread : threads)
                {
                    thread->join();
                }
            }
            // just gracefully do the multiply operation on the application thread if the user provides 1 for the "numberOfThreads" parameter.
            else if (numberOfThreads == 1U)
            {
                this->multiplyRange(0, this->numberOfRows - 1U, otherMatrix, 0, otherMatrixNumOfColumns - 1U, out);
            }
        }
    }

    template class Matrix<int>;
    template class Matrix<float>;
    template class Matrix<double>;
    template class Matrix<unsigned>;
    template class Matrix<long>;
    template class Matrix<long long>;
    template class Matrix<long double>;
    template class Matrix<unsigned long>;
}

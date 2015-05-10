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

#include "MatrixBaseTestFixture.hpp"

void MatrixBaseTestFixture::setUp()
{
    this->matrix1   =   std::make_shared< MatrixBase<int> >(3, 3);
    this->matrix2   =   std::make_shared< MatrixBase<double> >(2, 5, 3.141592653);
    this->matrix3   =   std::make_shared< MatrixBase<unsigned> >(5, 7);
    this->matrix4   =   std::make_shared< MatrixBase<float> >(10, 10);
    this->matrix5   =   std::make_shared< MatrixBase<double> >(2, 5, 3.141592653);
    this->matrix6   =   std::make_shared< MatrixBase<int> >(3, 3, 1);
    this->matrix7   =   std::make_shared< MatrixBase<unsigned> >(5, 7);
    this->matrix8   =   std::make_shared< MatrixBase<float> >(10, 10, 1.07);
    this->matrix9   =   std::make_shared< MatrixBase<int> >(4, 9, 2);
    this->matrix10  =   std::make_shared< MatrixBase<double> >(5, 5, 2.718237);

    this->matrix1->setElement(0, 0, 1);
    this->matrix1->setElement(1, 1, 1);
    this->matrix1->setElement(2, 2, 1);

    std::vector<float> temp     =   { 3.14, 5.17, 1.007, 2.30, 10.1, 1.25, 3.37, 2.718, 5.23, 7.09 };
    unsigned numOfRows          =   this->matrix4->getNumOfRows();
    unsigned numOfColumns       =   this->matrix4->getNumOfColumns();
    for (unsigned row = 0U; row < numOfRows; row++)
        for (unsigned col = 0U; col < numOfColumns; col++)
            this->matrix4->setElement(row, col, temp[col]);
}

void MatrixBaseTestFixture::testIsSquare()
{
    CPPUNIT_ASSERT(this->matrix1->isSquare()); // a 3 x 3 matrix should be square
    CPPUNIT_ASSERT(!this->matrix2->isSquare()); // a 2 x 5 matrix should not be square
    CPPUNIT_ASSERT(!this->matrix3->isSquare()); // a 5 x 7 matrix should not be square
    CPPUNIT_ASSERT(this->matrix4->isSquare()); // a 10 x 10 matrix should be square
}

void MatrixBaseTestFixture::testIsZero()
{
    int matrix1NumOfRows    =   this->matrix1->getNumOfRows();
    int matrix1NumOfCols    =   this->matrix1->getNumOfColumns();
    for (int matrix1Row = 0; matrix1Row < matrix1NumOfRows; matrix1Row++)
        for (int matrix1Col = 0; matrix1Col < matrix1NumOfCols; matrix1Col++)
            this->matrix1->setElement(matrix1Row, matrix1Col, 0);

    CPPUNIT_ASSERT(this->matrix1->isZero()); // Should be the Zero Matrix.
    CPPUNIT_ASSERT(this->matrix3->isZero()); // "
    CPPUNIT_ASSERT(this->matrix7->isZero()); // "

    CPPUNIT_ASSERT(!this->matrix2->isZero());  // Should not be the Zero Matrix.
    CPPUNIT_ASSERT(!this->matrix10->isZero()); // "
    CPPUNIT_ASSERT(!this->matrix5->isZero());  // "
    CPPUNIT_ASSERT(!this->matrix6->isZero());  // "
}

void MatrixBaseTestFixture::testIsIdentity()
{
    this->matrix1   =   std::make_shared< MatrixBase<int> >(3, 3);
    this->matrix6   =   std::make_shared< MatrixBase<int> >(5, 5);

    CPPUNIT_ASSERT(!this->matrix1->isIdentity()); // The Zero Matrix is not the Identity Matrix.

    (*(this->matrix1))[0][0] = 1; (*(this->matrix1))[1][1] = 1; (*(this->matrix1))[2][2] = 1;
    CPPUNIT_ASSERT(this->matrix1->isIdentity()); // All 1's on the diagonal with 0's everywhere else should be the Identity Matrix.

    int matrix6NumOfRows = this->matrix6->getNumOfRows();
    for (int row = 0; row < matrix6NumOfRows; row++)
        (*(this->matrix6))[row][row] = 1;
    CPPUNIT_ASSERT(this->matrix6->isIdentity()); // Should also be the Identity Matrix.

    CPPUNIT_ASSERT(!this->matrix2->isIdentity()); // A non-square matrix cannot be the Identity Matrix.

    CPPUNIT_ASSERT(!this->matrix10->isIdentity()); // A square matrix with all then entries equal to 2.718237 should not be the Identity Matrix.

    for (int row = 0; row < matrix6NumOfRows; row++)
        (*(this->matrix6))[row][row] = 6;
    CPPUNIT_ASSERT(!this->matrix6->isIdentity()); // A matrix with a value of 6 across the diagonal and 0 every where else should not be the Identity Matrix.
}

void MatrixBaseTestFixture::testEqual()
{
    CPPUNIT_ASSERT(this->matrix2->equal(*(this->matrix5))); // matrices should be equal because their dimensions and corresponding elements should be equal
    CPPUNIT_ASSERT(*(this->matrix2) == *(this->matrix5));
    CPPUNIT_ASSERT(this->matrix3->equal(*(this->matrix7)));
    CPPUNIT_ASSERT(*(this->matrix3) == *(this->matrix7));

    CPPUNIT_ASSERT(this->matrix1->equal(*(this->matrix1))); // a matrix should be equal to itself
    CPPUNIT_ASSERT(*(this->matrix1) == *(this->matrix1));
    CPPUNIT_ASSERT(this->matrix4->equal(*(this->matrix4)));
    CPPUNIT_ASSERT(*(this->matrix4) == *(this->matrix4));

    CPPUNIT_ASSERT(!this->matrix5->equal(*(this->matrix10))); // matrices of different dimensions should never be equal
    CPPUNIT_ASSERT(*(this->matrix5) != *(this->matrix10));
    CPPUNIT_ASSERT(!this->matrix6->equal(*(this->matrix9)));
    CPPUNIT_ASSERT(*(this->matrix6) != *(this->matrix9));

    CPPUNIT_ASSERT(!this->matrix1->equal(*(this->matrix6))); // matrices of the same dimensions but different elements should never be equal
    CPPUNIT_ASSERT(*(this->matrix1) != *(this->matrix6));
    CPPUNIT_ASSERT(!this->matrix4->equal(*(this->matrix8)));
    CPPUNIT_ASSERT(*(this->matrix4) != *(this->matrix8));
}

void MatrixBaseTestFixture::testAssignmentOverload()
{

}

void MatrixBaseTestFixture::testConstructor()
{
    CPPUNIT_ASSERT(this->matrix1->getNumOfRows() == 3U && this->matrix1->getNumOfColumns() == 3U);

    unsigned matrix2NumOfCols   =   this->matrix2->getNumOfColumns();
    unsigned matrix2NumOfRows   =   this->matrix2->getNumOfRows();
    CPPUNIT_ASSERT(matrix2NumOfRows == 2U && matrix2NumOfCols == 5U);
    for (unsigned row = 0U; row < matrix2NumOfRows; row++)
        for (unsigned col = 0U; col < matrix2NumOfCols; col++)
            CPPUNIT_ASSERT(isCloseEnough(3.141592653, this->matrix2->getElement(row, col), 0.000000001));

    unsigned matrix3NumOfColumns   =   this->matrix3->getNumOfColumns();
    unsigned matrix3NumOfRows   =   this->matrix3->getNumOfRows();
    for (unsigned row = 0U; row < matrix3NumOfRows; row++)
        for (unsigned col = 0U; col < matrix3NumOfColumns; col++)
            CPPUNIT_ASSERT(this->matrix3->getElement(row, col) == 0U);

    unsigned matrix4NumOfColumns   =   this->matrix4->getNumOfColumns();
    unsigned matrix4NumOfRows   =   this->matrix2->getNumOfRows();
    std::vector<float> temp = { 3.14, 5.17, 1.007, 2.30, 10.1, 1.25, 3.37, 2.718, 5.23, 7.09 };
    for (unsigned row = 0U; row < matrix4NumOfRows; row++)
        for (unsigned col = 0U; col < matrix4NumOfColumns; col++)
            CPPUNIT_ASSERT(isCloseEnough(temp[col], this->matrix4->getElement(row, col), 0.000001));
}

CppUnit::TestSuite* MatrixBaseTestFixture::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("MatrixBaseTestFixture");
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testConstructor", &MatrixBaseTestFixture::testConstructor));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testEqual", &MatrixBaseTestFixture::testEqual));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testIsSquare", &MatrixBaseTestFixture::testIsSquare));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testGetElement", &MatrixBaseTestFixture::testGetElement));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testSetElement", &MatrixBaseTestFixture::testSetElement));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testIsZero", &MatrixBaseTestFixture::testIsZero));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testIsIdentity", &MatrixBaseTestFixture::testIsIdentity));

    return suite;
}

void MatrixBaseTestFixture::testGetElement()
{
    CPPUNIT_ASSERT(isCloseEnough(this->matrix4->getElement(0, 0), 3.14, 0.000001));
    CPPUNIT_ASSERT(isCloseEnough(this->matrix4->getElement(1, 1), 5.17, 0.000001));
    CPPUNIT_ASSERT(this->matrix1->getElement(1, 1) == 1);
    CPPUNIT_ASSERT(isCloseEnough(this->matrix2->getElement(1, 1), 3.141592653, 0.0000000000001));
    CPPUNIT_ASSERT(isCloseEnough(this->matrix10->getElement(2, 2), 2.718237, 0.00000000000001));
    CPPUNIT_ASSERT(isCloseEnough(this->matrix8->getElement(1, 1), 1.07, 0.000001));
    CPPUNIT_ASSERT(this->matrix7->getElement(0, 0) == 0);
}

void MatrixBaseTestFixture::testSetElement()
{
    this->matrix4->setElement(0, 0, 6.937);
    CPPUNIT_ASSERT(isCloseEnough(this->matrix4->getElement(0, 0), 6.937, 0.000001));

    this->matrix1->setElement(0, 0, 29);
    CPPUNIT_ASSERT(this->matrix1->getElement(0, 0) == 29);

    this->matrix1->setElement(2, 2, 377);
    CPPUNIT_ASSERT(this->matrix1->getElement(2, 2) == 377);

    unsigned matrix9NumberOfRows = this->matrix9->getNumOfRows();
    for (unsigned row = 0U; row < matrix9NumberOfRows; row++)
    {
        this->matrix9->setElement(row, 0, 297);
        CPPUNIT_ASSERT(this->matrix9->getElement(row, 0) == 297);
    }
}

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(MatrixBaseTestFixture::suite());
    runner.run();
}

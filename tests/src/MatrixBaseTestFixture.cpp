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
    this->matrix5   =   std::make_shared< MatrixBase<double> >(2, 5, 3.141492653);

    this->matrix1->setElement(0, 0, 1);
    this->matrix1->setElement(1, 1, 1);
    this->matrix1->setElement(2, 2, 1);

    std::vector<float> temp = { 3.14, 5.17, 1.007, 2.30, 10.1, 1.25, 3.37, 2.718, 5.23, 7.09 };
    for (unsigned row = 0U; row < this->matrix4->getNumOfRows(); row++)
        for (unsigned col = 0U; col < this->matrix4->getNumOfColumns(); col++)
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

}

void MatrixBaseTestFixture::testIsIdentity()
{

}

void MatrixBaseTestFixture::testEqual()
{
    CPPUNIT_ASSERT(this->matrix2->equal(*(this->matrix5))); // matrices should be equal because their dimensions and corresponding elements should be equal
}

void MatrixBaseTestFixture::testAssignmentOverload()
{

}

void MatrixBaseTestFixture::testConstructor()
{
    CPPUNIT_ASSERT(this->matrix1->getNumOfRows() == 3U && this->matrix1->getNumOfColumns() == 3U);

    CPPUNIT_ASSERT(this->matrix2->getNumOfRows() == 2U && this->matrix2->getNumOfColumns() == 5U);
    for (unsigned row = 0U; row < this->matrix2->getNumOfRows(); row++)
        for (unsigned col = 0U; col < this->matrix2->getNumOfColumns(); col++)
            CPPUNIT_ASSERT(isCloseEnough<double>(3.141592653, this->matrix2->getElement(row, col), 0.000000001));

    for (unsigned row = 0U; row < this->matrix3->getNumOfRows(); row++)
        for (unsigned col = 0U; col < this->matrix3->getNumOfColumns(); col++)
            CPPUNIT_ASSERT(this->matrix3->getElement(row, col) == 0U);

    std::vector<float> temp = { 3.14, 5.17, 1.007, 2.30, 10.1, 1.25, 3.37, 2.718, 5.23, 7.09 };
    for (unsigned row = 0U; row < this->matrix4->getNumOfRows(); row++)
        for (unsigned col = 0U; col < this->matrix4->getNumOfColumns(); col++)
            CPPUNIT_ASSERT(isCloseEnough<float>(temp[col], this->matrix4->getElement(row, col), 0.000001));
}

static CppUnit::TestSuite* suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("MatrixBaseTestFixture");
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testConstructor", &MatrixBaseTestFixture::testConstructor));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testEqual", &MatrixBaseTestFixture::testEqual));
    suite->addTest(new CppUnit::TestCaller<MatrixBaseTestFixture>("testIsSquare", &MatrixBaseTestFixture::testIsSquare));
}

void MatrixBaseTestFixture::testGetElement()
{

}

void MatrixBaseTestFixture::testSetElement()
{

}

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(MatrixBaseTestFixture::suite());
    runner.run();
}

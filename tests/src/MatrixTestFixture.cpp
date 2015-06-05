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

#include <MatrixTestFixture.hpp>

CppUnit::TestSuite* MatrixTestFixture::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("MatrixTestFixture");
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testAssignmentOverload", &MatrixTestFixture::testAssignmentOverload));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testScale", &MatrixTestFixture::testScale));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testPower", &MatrixTestFixture::testPower));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testAddRange", &MatrixTestFixture::testAddRange));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testSubtractRange", &MatrixTestFixture::testSubtractRange));

    return suite;
}

void MatrixTestFixture::testAssignmentOverload()
{
    *(this->testMatrix2) = *(this->testMatrix1); // testMatrix1 has less columns and rows than testMatrix2.
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == 1);

    *(this->testMatrix1) = *(this->testMatrix2); // testMatrix2 has more rows and columns than testMatrix1.
    CPPUNIT_ASSERT(*(this->testMatrix1) == *(this->testMatrix2));

    Matrix<int> matrix1(5, 5, 1);
    matrix1 = *(this->testMatrix3); // testMatrix3 has more columns and the same number of rows as testMatrix1.
    CPPUNIT_ASSERT(matrix1 == *(this->testMatrix3));

    *(this->testMatrix2) = *(this->testMatrix7); // testMatrix7 has more rows and the same number of columns as testMatrix2.
    CPPUNIT_ASSERT(*(this->testMatrix2) == *(this->testMatrix7));
}

void MatrixTestFixture::setUp()
{
    this->testMatrix1   =   std::make_shared< Matrix<int> >(5, 5, 1);
    
    this->testMatrix2   =   std::make_shared< Matrix<int> >(10, 10);
    std::vector<int> temp {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (unsigned row = 0U; row < 10U; row++)
        for (unsigned col = 0U; col < 10U; col++)
            (*(this->testMatrix2))[row][col] = temp[col];

    this->testMatrix4   =   std::make_shared< Matrix<double> >(4, 4, 3.141592653);
    this->testMatrix3   =   std::make_shared< Matrix<int> >(5, 7, 2);
    this->testMatrix7   =   std::make_shared< Matrix<int> >(11, 10, 3);
    this->testMatrix5   =   std::make_shared< Matrix<double> >(5, 4, 2.71812);
    this->testMatrix6   =   std::make_shared< Matrix<double> >(7, 5);
    std::vector<double> temp2 {0.00001, 0.00002, 0.00003, 0.00004, 0.00005, 0.00006, 0.00007};
    for (unsigned row = 0U; row < 7U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            (*(this->testMatrix6))[row][col] = temp2[row];

    this->testMatrix11 = std::make_shared< Matrix<int> >(5, 5, 3);

    std::vector<int> temp3 {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    this->testMatrix8 = std::make_shared< Matrix<int> >(10, 10);
    for (unsigned row = 0U; row < 10U; row++)
        for (unsigned col = 0U; col < 10U; col++)
            (*(this->testMatrix8))[row][col] = temp3[col];

    this->testMatrix9 = std::make_shared< Matrix<double> >(4, 4, 3.141592653);

    this->testMatrix10 = std::make_shared< Matrix<double> >(7, 5);
    std::vector<double> temp4 {-1e-5, -2e-5, -3e-5, -4e-5, -5e-5, -6e-5, -7e-5};
    for (unsigned row = 0U; row < 7U; row++)
        for (unsigned col = 0U; col < 5U; col++)
        (*(this->testMatrix10))[row][col] = temp4[row];
}

void MatrixTestFixture::testScale()
{
    this->testMatrix1->scale(2);
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 2);

    std::vector<int> temp {3, 6, 9, 12, 15, 18, 21, 24, 27, 30};
    this->testMatrix2->scale(3);
    for (unsigned row = 0U; row < 10U; row++)
        for (unsigned col = 0U; col < 10U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == temp[col]);

    this->testMatrix3->scale(1);
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 7U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix3))[row][col] == 2);

    this->testMatrix4->scale(2.00);
    CPPUNIT_ASSERT(this->testMatrix4->allElementsAre(6.283185306));

    this->testMatrix5->scale(2.71812);
    CPPUNIT_ASSERT(this->testMatrix5->allElementsAre(7.3881763344));

    for (unsigned row = 0U; row < 7U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            this->testMatrix6->scale((*(this->testMatrix6))[row][col]);
    std::vector<double> temp2 {1e-10, 4e-10, 9e-10, 1.6e-9, 2.5e-9, 3.6e-9, 4.9e-9};
    for (unsigned row = 0U; row < 7U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT(isCloseEnough(temp2[row], (*(this->testMatrix6))[row][col], 0.0000001));
}

void MatrixTestFixture::testPower()
{
    this->testMatrix1->power(2.00); // matrix^2
    CPPUNIT_ASSERT(this->testMatrix1->allElementsAre(1)); 

    this->testMatrix2->power(0.5); // you can even do square roots!
    std::vector<int> temp {1, 1, 1, 2, 2, 2, 2, 2, 3, 3};
    for (unsigned row = 0U; row < 10U; row++)
        for (unsigned col = 0U; col < 10U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == temp[col]);

    this->testMatrix3->power(3.00); // matrix^3
    CPPUNIT_ASSERT(this->testMatrix3->allElementsAre(8));

    this->testMatrix4->power(3.141592653); // crazy fractional exponents
    CPPUNIT_ASSERT(this->testMatrix4->allElementsAre(36.462159561085));

    this->testMatrix5->power(1.00); // matrix^1 should equal matrix (itself without modifications).
    CPPUNIT_ASSERT(this->testMatrix5->allElementsAre(2.71812));

    this->testMatrix6->power(0.00); // matrix^0 should yield a matrix of all 1's.
    CPPUNIT_ASSERT(this->testMatrix6->allElementsAre(1.00));
}

void MatrixTestFixture::testAddRange()
{
    this->testMatrix4->addRange(*(this->testMatrix9), 0, 0); // Try adding only a single row of each matrix together.
    for (unsigned col = 0U; col < 4U; col++)
        CPPUNIT_ASSERT(isCloseEnough(6.283185306, (*(this->testMatrix4))[0][col], 0.000000001)); 

    this->testMatrix2->addRange(*(this->testMatrix8), 0, 9); // Add two entire matrices.
    CPPUNIT_ASSERT(this->testMatrix2->allElementsAre(10));

    this->testMatrix6->addRange(*(this->testMatrix10), 0, 6); // "
    CPPUNIT_ASSERT(this->testMatrix6->allElementsAre(0.00));

    this->testMatrix11->addRange(*(this->testMatrix1), 4, 5); // Try an out of range row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix6->addRange(*(this->testMatrix9), 0, 2); // Try adding two matrices with unequal dimensions. Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix6->allElementsAre(0.00)); 

    this->testMatrix11->addRange(*(this->testMatrix1), 3, 2); // Try specifying a row start index greater than the row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix11->addRange(*(this->testMatrix1), 5, 2); // Try specifying an out of range row start index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix7->addRange(*(this->testMatrix8), 0, 10); // Try adding matrices with a different number of rows and the same number of columns. 
                                                              // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix7->allElementsAre(3));

    this->testMatrix1->addRange(*(this->testMatrix3), 0, 4); // Try adding two matrices with the same number of rows and a different number of columns. 
                                                             // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix1->allElementsAre(1));

    this->testMatrix1->addRange(*(this->testMatrix11), 0, 2); // Add a valid row range of two matrices.
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            if (row <= 2U)
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 4);
            else
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 1);
}

void MatrixTestFixture::testSubtractRange()
{
    this->testMatrix4->SubtractRange(*(this->testMatrix9), 0, 0); // Try subtracting only a single row of each matrix together.
    for (unsigned col = 0U; col < 4U; col++)
        CPPUNIT_ASSERT(isCloseEnough(6.283185306, (*(this->testMatrix4))[0][col], 0.000000001)); 

    this->testMatrix2->SubtractRange(*(this->testMatrix8), 0, 9); // Subtract two entire matrices.
    CPPUNIT_ASSERT(this->testMatrix2->allElementsAre(10));

    this->testMatrix6->SubtractRange(*(this->testMatrix10), 0, 6); // "
    CPPUNIT_ASSERT(this->testMatrix6->allElementsAre(0.00));

    this->testMatrix11->SubtractRange(*(this->testMatrix1), 4, 5); // Try an out of range row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix6->SubtractRange(*(this->testMatrix9), 0, 2); // Try subtracting two matrices with unequal dimensions. Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix6->allElementsAre(0.00)); 

    this->testMatrix11->SubtractRange(*(this->testMatrix1), 3, 2); // Try specifying a row start index greater than the row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix11->SubtractRange(*(this->testMatrix1), 5, 2); // Try specifying an out of range row start index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix7->SubtractRange(*(this->testMatrix8), 0, 10); // Try subtracting matrices with a different number of rows and the same number of columns. 
                                                              // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix7->allElementsAre(3));

    this->testMatrix1->SubtractRange(*(this->testMatrix3), 0, 4); // Try subtracting two matrices with the same number of rows and a different number of columns. 
                                                             // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix1->allElementsAre(1));

    this->testMatrix1->SubtractRange(*(this->testMatrix11), 0, 2); // Subtract a valid row range of two matrices.
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            if (row <= 2U)
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 4);
            else
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 1);
}

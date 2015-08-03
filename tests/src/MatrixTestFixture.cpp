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
#include <iostream>

CppUnit::TestSuite* MatrixTestFixture::suite()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("MatrixTestFixture");
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testAssignmentOverload", &MatrixTestFixture::testAssignmentOverload));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testScale", &MatrixTestFixture::testScale));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testPower", &MatrixTestFixture::testPower));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testAddRange", &MatrixTestFixture::testAddRange));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testSubtractRange", &MatrixTestFixture::testSubtractRange));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testMultiplyRange", &MatrixTestFixture::testMultiplyRange));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testAdditionOperatorOverload", &MatrixTestFixture::testAdditionOperatorOverload));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testSubtractionOperatorOverload", &MatrixTestFixture::testSubtractionOperatorOverload));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testParallelAdd", &MatrixTestFixture::testParallelAdd));
    suite->addTest(new CppUnit::TestCaller<MatrixTestFixture>("testParallelSubtract", &MatrixTestFixture::testParallelSubtract));

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

    this->testMatrix12  =   std::make_shared< Matrix<int> >(1000, 1000, 1);
    this->testMatrix13  =   std::make_shared< Matrix<int> >(1000, 1000, 1);
    this->testMatrix14  =   std::make_shared< Matrix<double> >(1327, 1327, 1.0);
    this->testMatrix15  =   std::make_shared< Matrix<double> >(1327, 1327, 2.0);
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
    this->testMatrix4->subtractRange(*(this->testMatrix9), 0, 0); // Try subtracting only a single row of each matrix together.
    for (unsigned row = 0U; row < 4U; row++)
        for (unsigned col = 0U; col < 4U; col++)
            if (row == 0)
                CPPUNIT_ASSERT(isCloseEnough(0.00, (*(this->testMatrix4))[row][col], 0.000000001));
            else
                CPPUNIT_ASSERT(isCloseEnough(3.141592653, (*this->testMatrix4)[row][col], 0.000000001));

    this->testMatrix8->subtractRange(*(this->testMatrix2), 0, 9); // Subtract two entire matrices.
    std::vector<int> temp {8, 6, 4, 2, 0, -2, -4, -6, -8, -10};
    for (unsigned row = 0U; row <= 9; row++)
        for (unsigned col = 0U; col <= 9; col++)
            CPPUNIT_ASSERT((*(this->testMatrix8))[row][col] == temp[col]);

    this->testMatrix6->subtractRange(*(this->testMatrix10), 0, 6); // "
    std::vector<double> temp2 {1e-5, 2e-5, 3e-5, 4e-5, 5e-5, 6e-5, 7e-5};
    for (unsigned row = 0U; row <= 6; row++)
        for (unsigned col = 0U; col <= 4; col++)
            CPPUNIT_ASSERT(isCloseEnough(2.00 * temp2[row], (*(this->testMatrix6))[row][col], 1e-8));

    this->testMatrix11->subtractRange(*(this->testMatrix1), 4, 5); // Try an out of range row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix6->subtractRange(*(this->testMatrix9), 0, 2); // Try subtracting two matrices with unequal dimensions. Expect nothing to happen.
    for (unsigned row = 0U; row <= 6; row++)
        for (unsigned col = 0U; col <= 4; col++)
            CPPUNIT_ASSERT(isCloseEnough(2.00 * temp2[row], (*(this->testMatrix6))[row][col], 1e-8)); 

    this->testMatrix11->subtractRange(*(this->testMatrix1), 3, 2); // Try specifying a row start index greater than the row end index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix11->subtractRange(*(this->testMatrix1), 5, 2); // Try specifying an out of range row start index. Nothing should happen.
    CPPUNIT_ASSERT(this->testMatrix11->allElementsAre(3));

    this->testMatrix7->subtractRange(*(this->testMatrix8), 0, 10); // Try subtracting matrices with a different number of rows and the same number of columns. 
                                                              // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix7->allElementsAre(3));

    this->testMatrix1->subtractRange(*(this->testMatrix3), 0, 4); // Try subtracting two matrices with the same number of rows and a different number of columns. 
                                                             // Expect nothing to happen.
    CPPUNIT_ASSERT(this->testMatrix1->allElementsAre(1));

    this->testMatrix1->subtractRange(*(this->testMatrix11), 0, 2); // Subtract a valid row range of two matrices.
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            if (row <= 2U)
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == -2);
            else
                CPPUNIT_ASSERT((*(this->testMatrix1))[row][col] == 1);
}

void MatrixTestFixture::testMultiplyRange()
{
    Matrix<int> testOutput1(10, 10);
    std::vector<int> temp {45, 90, 135, 180, 225, 270, 315, 360, 405, 450};
    this->testMatrix8->multiplyRange(0, 9, *(this->testMatrix2), 0, 9, testOutput1); // Multiply two entire matrices.
    for (unsigned row = 0; row < 10U; row++)
        for (unsigned col = 0; col < 10U; col++)
            CPPUNIT_ASSERT(testOutput1[row][col] == temp[col]);

    Matrix<int> testOutput11(3, 3);
    Matrix<int> testInput11(3, 3, 2);
    Matrix<int> testInput11b(3, 3, 3);                                      /*                 "  another test             */
    testInput11.multiplyRange(0, 2, testInput11b, 0, 2, testOutput11);
    CPPUNIT_ASSERT(testOutput11.allElementsAre(18));


    Matrix<int> testOutput2(5, 7);
    this->testMatrix1->multiplyRange(1, 3, *(this->testMatrix3), 1, 3, testOutput2); // Multiply a part of two matrices.
    for (unsigned row = 0; row < 5U; row++)
        for (unsigned col = 0; col < 7U; col++)
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
                CPPUNIT_ASSERT(testOutput2[row][col] == 10);
            else
                CPPUNIT_ASSERT(testOutput2[row][col] == 0);

    Matrix<int> testOutput12(3, 3);                                         // " another test
    testInput11.multiplyRange(2, 2, testInput11b, 0, 0, testOutput12);
    CPPUNIT_ASSERT(testOutput12[2][0] == 18);
    for (unsigned row = 0U; row <= 2; row++)
        for (unsigned col = 0U; col <= 2; col++)
            if (row != 2 && col != 0)
                CPPUNIT_ASSERT(testOutput12[row][col] == 0);

    testOutput2.multiplyRange(9, 3, testOutput2, 9, 3, testOutput2); // Try an invalid start index. Nothing should happen.
    for (unsigned row = 0; row < 5U; row++)
        for (unsigned col = 0; col < 7U; col++)
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
                CPPUNIT_ASSERT(testOutput2[row][col] == 10);
            else
                CPPUNIT_ASSERT(testOutput2[row][col] == 0);

    testOutput2.multiplyRange(0, 8, testOutput2, 0, 8, testOutput2); // Try an invalid end index. Nothing should happen.
    for (unsigned row = 0; row < 5U; row++)
        for (unsigned col = 0; col < 7U; col++)
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
                CPPUNIT_ASSERT(testOutput2[row][col] == 10);
            else
                CPPUNIT_ASSERT(testOutput2[row][col] == 0);

    Matrix<double> testOutput3(7, 4);
    this->testMatrix6->multiplyRange(4, 6, *(this->testMatrix5), 0, 2, testOutput3); // Multiply two different ranges of two different matrices.
    for (unsigned row = 0; row < 7U; row++)
    {
        for (unsigned col = 0; col < 4U; col++)
        {
            if (row >= 4 && row <= 6 && col <= 2)
            {
                switch (row)
                {
                    case 4:
                        CPPUNIT_ASSERT(isCloseEnough(0.00067953, testOutput3[row][col], 0.0000000001));
                        break;
                    case 5:
                        CPPUNIT_ASSERT(isCloseEnough(0.000815436, testOutput3[row][col], 0.0000000001));
                        break;
                    case 6:
                        CPPUNIT_ASSERT(isCloseEnough(0.000951342, testOutput3[row][col], 0.0000000001));
                        break;
                }
            }
            else
            {
                CPPUNIT_ASSERT(isCloseEnough(0.00, testOutput3[row][col], 0.000000001));
            }
        }
    }
}

void MatrixTestFixture::testAdditionOperatorOverload()
{
   auto test1Output = *(this->testMatrix4) + *(this->testMatrix9);
   CPPUNIT_ASSERT(test1Output->allElementsAre(6.283185306));

   auto test2Output = *(this->testMatrix4) + *(this->testMatrix5);
   CPPUNIT_ASSERT(test2Output->allElementsAre(0.00)); // the output should be a zero matrix because we  tried to add matrices of different dimensions.

   auto test3Output = *(this->testMatrix1) + *(this->testMatrix11);
   CPPUNIT_ASSERT(test3Output->allElementsAre(4));

   auto test4Output = *(this->testMatrix6) + *(this->testMatrix10);
   CPPUNIT_ASSERT(test4Output->allElementsAre(0.0));

   auto test5Output = *(this->testMatrix2) + *(this->testMatrix8);
   CPPUNIT_ASSERT(test5Output->allElementsAre(10));
}

void MatrixTestFixture::testSubtractionOperatorOverload()
{
    auto test1Output = *(this->testMatrix4) - *(this->testMatrix9);
    CPPUNIT_ASSERT(test1Output->allElementsAre(0.0));

    auto test2Output = *(this->testMatrix1) - *(this->testMatrix11);
    CPPUNIT_ASSERT(test2Output->allElementsAre(-2));

    auto test3Output = *(this->testMatrix5) - *(this->testMatrix6);
    CPPUNIT_ASSERT(test3Output->allElementsAre(0.0)); // We should receive a zero matrix as output because we tried to subtract two matrices with different dimensions.

    std::vector<double> temp { 2e-5, 4e-5, 6e-5, 8e-5, 1e-4, 1.2e-4, 1.4e-4 };
    auto test4Output = *(this->testMatrix6) - *(this->testMatrix10);
    for (unsigned row = 0U; row < 7U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT((*test4Output)[row][col] == temp[row]);

    auto test5Output = *(this->testMatrix11) - *(this->testMatrix1);
    CPPUNIT_ASSERT(test5Output->allElementsAre(2));
}

void MatrixTestFixture::testParallelAdd()
{
    this->testMatrix12->parallelAdd(*(this->testMatrix13), 2);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(2));

    this->testMatrix12->parallelAdd(*(this->testMatrix13), 3);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(3));

    this->testMatrix12->parallelAdd(*(this->testMatrix13), 4);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(4));

    this->testMatrix13->parallelAdd(*(this->testMatrix12), 1); // make sure that parallelAdd does not crash when invoked with a thread count of only one.
    CPPUNIT_ASSERT(this->testMatrix13->allElementsAre(5));

    // make sure that parallelAdd does not crash when called with a higher thread count than my MacBook Pro can support concurrently.
    this->testMatrix12->parallelAdd(*(this->testMatrix13), 10);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(9));

    this->testMatrix14->parallelAdd(*(this->testMatrix15), 4); // Try adding matrices with an odd number of rows on an even number of threads.
    CPPUNIT_ASSERT(this->testMatrix14->allElementsAre(3.0));

    this->testMatrix15->parallelAdd(*(this->testMatrix14), 3); // odd number of rows and odd number of threads.
    CPPUNIT_ASSERT(this->testMatrix15->allElementsAre(5.0));
}

// minimal tests for Matrix<ElemType>::parallelSubtract because the logic is very similar to Matrix<ElemType>::parallelAdd
void MatrixTestFixture::testParallelSubtract()
{
    this->testMatrix12->parallelSubtract(*(this->testMatrix13), 2);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(0));

    this->testMatrix12->parallelSubtract(*(this->testMatrix13), 3);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(-1));

    this->testMatrix12->parallelSubtract(*(this->testMatrix13), 4);
    CPPUNIT_ASSERT(this->testMatrix12->allElementsAre(-2));

    this->testMatrix14->parallelSubtract(*(this->testMatrix15), 3); // Try parallel subtracting on odd number of rows on an odd number of threads.
    CPPUNIT_ASSERT(this->testMatrix14->allElementsAre(-1.00));

    this->testMatrix14->parallelSubtract(*(this->testMatrix15), 4); // odd number of rows--even number of threads.
    CPPUNIT_ASSERT(this->testMatrix14->allElementsAre(-3.00));
}

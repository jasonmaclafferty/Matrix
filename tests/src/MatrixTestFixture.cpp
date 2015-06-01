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

    return suite;
}

void MatrixTestFixture::testAssignmentOverload()
{
    *(this->testMatrix2) = *(this->testMatrix1); // testMatrix1 has less columns and rows than testMatrix2
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == 1);

    *(this->testMatrix1) = *(this->testMatrix2); // testMatrix2 has more rows and columns than testMatrix1
    CPPUNIT_ASSERT(*(this->testMatrix1) == *(this->testMatrix2));

    Matrix<int> matrix1(5, 5, 1);
    matrix1 = *(this->testMatrix3); // testMatrix3 has more columns and the same number of rows as testMatrix1
    CPPUNIT_ASSERT(matrix1 == *(this->testMatrix3));

    *(this->testMatrix2) = *(this->testMatrix7); // testMatrix7 has more rows and the same number of columns as testMatrix2
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
    this->testMatrix1->power(2.00);
    CPPUNIT_ASSERT(this->testMatrix1->allElementsAre(1)); 

    this->testMatrix2->power(0.5); // you can even do square roots!
    std::vector<int> temp {1, 1, 1, 2, 2, 2, 2, 2, 3, 3};
    for (unsigned row = 0U; row < 10U; row++)
        for (unsigned col = 0U; col < 10U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == temp[col]);

    this->testMatrix3->power(3.00);
    CPPUNIT_ASSERT(this->testMatrix3->allElementsAre(3.00));
}

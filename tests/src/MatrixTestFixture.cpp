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

    return suite;
}

void MatrixTestFixture::testAssignmentOverload()
{
    *(this->testMatrix1) = *(this->testMatrix2); // testMatrix2 has more rows and columns than testMatrix1
    CPPUNIT_ASSERT(*(this->testMatrix1) == *(this->testMatrix2));

    *(this->testMatrix2) = *(this->testMatrix1); // testMatrix1 has less columns and rows than testMatrix2
    for (unsigned row = 0U; row < 5U; row++)
        for (unsigned col = 0U; col < 5U; col++)
            CPPUNIT_ASSERT((*(this->testMatrix2))[row][col] == 1);

    *(this->testMatrix1) = *(this->testMatrix3); // testMatrix3 has more columns and the same number of rows as testMatrix1
    CPPUNIT_ASSERT(*(this->testMatrix1) == *(this->testMatrix3));

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
}

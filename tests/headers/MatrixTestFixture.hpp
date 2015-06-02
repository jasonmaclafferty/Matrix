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

#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <memory>

#include <Matrix.hpp>
#include <Utility.hpp>

class MatrixTestFixture : public CppUnit::TestFixture
{
    protected:
        std::shared_ptr< Matrix<int> > testMatrix1;

        std::shared_ptr< Matrix<int> > testMatrix2;
        
        std::shared_ptr< Matrix<int> > testMatrix3;

        std::shared_ptr< Matrix<double> > testMatrix4;

        std::shared_ptr< Matrix<double> > testMatrix5;

        std::shared_ptr< Matrix<double> > testMatrix6;

        std::shared_ptr< Matrix<int> > testMatrix7;

        std::shared_ptr< Matrix<int> > testMatrix8;

        std::shared_ptr< Matrix<double> > testMatrix9;

        std::shared_ptr< Matrix<double> > testMatrix10;

        std::shared_ptr< Matrix<int> > testMatrix11;

    public:
        void testPower();

        void setUp();

        void testMultiplyRange();

        void testAddRange();

        void testSubtractRange();
        
        void testScale();

        void testAssignmentOverload();

        static CppUnit::TestSuite* suite();
};

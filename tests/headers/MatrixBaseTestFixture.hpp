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

#ifndef _MATRIXBASETESTFIXTURE_HPP_
#define _MATRIXBASETESTFIXTURE_HPP_

#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <memory>

#include "MatrixBase.hpp"
#include "Utility.hpp"

class MatrixBaseTestFixture : public CppUnit::TestFixture
{
    protected:
        std::shared_ptr< MatrixBase<int> > matrix1;

        std::shared_ptr< MatrixBase<double> > matrix2;

        std::shared_ptr< MatrixBase<unsigned> > matrix3;

        std::shared_ptr< MatrixBase<float> > matrix4;

        std::shared_ptr< MatrixBase<double> > matrix5;

    public:
        void setUp();

        void testConstructor();

        void testIsSquare();

        void testIsZero();

        void testIsIdentity();

        void testEqual();

        void testAssignmentOverload();

        void testGetElement();

        void testSetElement();

        static CppUnit::TestSuite* suite();
};

#endif

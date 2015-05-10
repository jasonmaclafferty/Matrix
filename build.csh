#!/bin/tcsh

# <Matrix--A matrix algorithm for doing matrix algebra.>
# Copyright (C) <2015> <Jason L MacLafferty>
# Contact me at: jason.maclafferty.93@gmail.com  
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set libraryBuildCmd     =   "clang++ -W -std=c++11 -shared -o lib/bin/libMatrix.dylib -Iutility/headers -Ilib/headers utility/src/Utility.cpp lib/src/*.cpp"
set testProgBuildCmd    =   "clang++ -W -std=c++11 -o tests/bin/tester -Ilib/headers -Iutility/headers -Itests/headers tests/src/*.cpp utility/src/Utility.cpp -L/usr/local/lib -Llib/bin -lcppunit -lMatrix"

if ($argv[1] == DEBUG || $argv[1] == debug || $argv[1] == d || $argv[1] == D || $argv[1] == Debug) then
    set libraryBuildCmd     =   "$libraryBuildCmd -g"
    set testProgBuildCmd    =   "$testProgBuildCmd -g"
endif

eval $libraryBuildCmd # build the library
eval $testProgBuildCmd # build the unit tests

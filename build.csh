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

set unitTestsBuildCmd   =   "clang++ -W -std=c++11 -o tests/bin/UnitTests -Ilib/headers -Iutility/headers -Itests/headers tests/src/TestRunner.cpp tests/src/*TestFixture.cpp utility/src/Utility.cpp -L/usr/local/lib -lcppunit -Llib/bin -lMatrix"
set ioTestsBuildCmd     =   "clang++ -W -std=c++11 -o tests/bin/IOTests -Iutility/headers -Ilib/headers utility/src/Utility.cpp tests/src/IOTest.cpp -Llib/bin -lMatrix"
set libraryBuildCmd     =   "clang++ -W -std=c++11 -shared -o lib/bin/libMatrix.dylib -Iutility/headers -Ilib/headers utility/src/Utility.cpp lib/src/*.cpp"
set speedTestsBuildCmd  =   "clang++ -Wall -Wextra -std=c++11 -o tests/bin/SpeedTests -Ilib/headers tests/src/SpeedTest.cpp -Llib/bin -lMatrix"

# check if the user specified a debug build or a build clean
if ($#argv > 0) then
    if ($argv[1] == DEBUG || $argv[1] == debug || $argv[1] == d || $argv[1] == D || $argv[1] == Debug) then
        set libraryBuildCmd     =   "$libraryBuildCmd -g"
        set unitTestsBuildCmd   =   "$unitTestsBuildCmd -g"
        set ioTestsBuildCmd     =   "$ioTestsBuildCmd -g"
    else if ($argv[1] == CLEAN || $argv[1] == clean || $argv[1] == Clean) then
        rm -rf ./lib/bin
        rm -rf ./tests/bin
        exit 0
    endif
endif

# check for the existance of the build directores and if necessary, create them.
if (!(-e ./lib/bin)) then
    mkdir ./lib/bin
endif
if (!(-e ./tests/bin)) then
    mkdir ./tests/bin
endif

eval $libraryBuildCmd       # build the library
eval $unitTestsBuildCmd     # build the unit tests
eval $ioTestsBuildCmd       # build the IO tests
eval $speedTestsBuildCmd    # build the speed tests

if ($? == 0) then
    echo "Build finished successfully."
endif

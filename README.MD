A simple matrix algorithm for doing matrix algebra.
One of the major design goals of this project is to support doing matrix algebra on a massive number of concurrent threads.

I wrote this project after taking an upper division data structures class in C++ my junior year of college.

Compile the shared library and tests from the current code base with the supplied build script (build.csh).
The build script currently only supports Mac OS X. You will need the OS X Commandline Developer Tools installed to build the library with the build script.
The CppUnit C++ unit testing framework must also be installed on your system for the build script to work. The assumption is that you installed CppUnit with homebrew and that your homebrew installation is in /usr/local.

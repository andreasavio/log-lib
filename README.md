The log_lib library
===================

Overview
--------

log_lib is a small, header-only logger library providing the following functions:

- Log messages with different severity levels: debug, info, warn, error, fatal;
- Write to multiple data streams, such as std::cout or file streams, from multiple threads;
- Ability to log default data types.

The library has been built and tested on msvc 12 (2013).


Contents
--------

The distribution contains the following:


### Library files ###

All library headers are found in the "include" folder.


### Demo and test programs ###

The source code includes a demo program and unit tests. The code is provided as a Visual Studio 2013 solution, log_lib.sln.


### Pre-built binaries ###

The pre-built demo and tests are found under "bin". Both programs are built on Release|32-bit.


### Documentation ###

In the "documentation" folder there are:

- A document named "documentation_and_rationale.txt" which describes the main features of the library, explains the design rationale and discusses possible improvements;
- The doxygen documentation for the project. Click on doxygen.html to view it.


Dependencies
------------

- Google Test [1] v. 1.7.0 is required to build the unit tests;

  [1] http://code.google.com/p/googletest

- CMake [2] is required to build Google Test (validated with v. 3.3.2).

  [2] http://cmake.org


Build and run
-------------

The core library is header-only. The demo application and the unit tests, on the other hand, require building.

The code is provided as a Visual Studio 2013 solution. It contains two projects:
- demo:  A simple command-line application demonstrating the library features;
- tests: The unit tests, which rely on the Google Test framework.


### Use the library ###

Simply include ./include/log_lib in your project path.


### Build and run the demo program ###

To build the program, open the solution in Visual Studio 2013 and build the "demo" project.

The demo program is a command-line application named demo.exe. It generates 100 log messages from two different threads and outputs them to the command line and to a file named demo_log_file.txt. The file is saved in the same folder as the program.

The program demonstrates the following features:

- Sending messages to multiple data streams from a single logger;
- Logging from multiple threads;
- Logging a custom data type.


### Build and run the unit tests ###

The library is unit-tested using the Google Test framework. In order to build the "tests" project, you first need to:

- Build the Google Test libraries from source;
- Configure the Visual Studio project with the library paths.

To build Google Test, download the source code [3] and follow the instructions provided in the README. Google Test uses CMake, a cross-platform tool that generates makefiles for your build environment of choice. The CMake build process is explained in the "Using CMake" section of the README. You can also build Google Test with your IDE of choice (see the "Generic Build Instruction" section) but you'll have to set it up manually.

  [3] https://github.com/google/googletest/releases

On Windows the default build process will create two libraries, gtest.lib and gtest_main.lib.

After building the Google Test libraries, you need to add them to the Visual Studio project. Let ${GTEST_ROOT_DIR} be the directory where you downloaded the Google Test code and ${GTEST_BUILD_DIR} the one where the libraries are. You need set up the VS project "tests" as follows:

- Add the headers path ${GTEST_ROOT_DIR}/include to the include directories of the project (Configuration Properties / C/C++ / Additional Include Directories), replacing placeholder __GTEST_INCLUDE__;
- Add the library path ${GTEST_BUILD_DIR} to the library directories of the project (Configuration Properties / Linker / Additional Library Directories), replacing placeholder __GTEST_LIBS_*__. You need to do this for each different configuration (Debug/Release, 32/64 bits...).

You can then build the "tests" project. This will create a command-line program called "tests.exe" that will run through all the test cases.

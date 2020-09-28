cmake_minimum_required(VERSION 3.13)

# set the project name and version
project(CloningCytosim VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tar)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# add some cmake options
option(BUILD_OBSERVABLE_EXECUTABLE 
	"build the executable which calculates the observable (in this case, rate of work wDot) from an input of Cytosim data" 
	ON
	)

option(BUILD_CLONING_EXECUTABLE 
	"build the executable which performs cloning algorithm with Cytosim" 
	OFF
	)

# add subdirectories (each containing its own CMakeLists.txt)
add_subdirectory(src/cloning)
add_subdirectory(src/observable)

# set the directory of the Eigen library
set(Eigen3_DIR ${PROJECT_SOURCE_DIR}/lib/eigen-3.3.7/cmake)


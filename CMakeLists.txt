cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(CloningCytosim VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add cxx17 flags
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++17")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++17")
elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++1z")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++1z")
endif()

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
	ON
	)

set(_SINGULARITY_PATH
	"/usr/bin/singularity"
	CACHE PATH
	"specify the path of the sinularity executable"
	)

set(_CYTOSIM_CONTAINER_PATH
	"/home/alexandra/temp/singularity/cytosim_container/cytosim.sif"
	CACHE PATH
	"specify the path of the cytosim singularity image file"
	)


# add subdirectories (each containing its own CMakeLists.txt)
add_subdirectory(src/wDot)
#add_subdirectory(src/axial_forces)
add_subdirectory(src/cloning)
add_subdirectory(src/calc_n_a)

cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Cloning Algorithm with Cytosim VERSION 1.0)

### FLAGS ###

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tar)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

option(BUILD_OBSERVABLE_EXECUTABLE "build the executable which calculates the observable (in this case, rate of work wDot) from an input of Cytosim data" ON)
option(BUILD_CLONING_EXECUTABLE "build the executable which performs cloning algorithm with Cytosim" ON)

### FILES ###

set(OBSERVABLE_SRC_DIR "${PROJECT_SOURCE_DIR}/src/observable")
set(CLONING_SRC_DIR "${PROJECT_SOURCE_DIR}/src/cloning")

set(OBSERVABLE_EXE_TARGET "calculate")
set(CLONING_EXE_TARGET "clone")

# use this to link against libraries (?)
set(CLONING_LIBRARIES
    ""
    )

### INCLUDE ###


### TARGET ###


### EXTERNAL LIBS ###
add_subdirectory(./lib/eigen-3.3.7/Eigen)
target_link_libraries(calculate Eigen)



# if you want to pass cmake settings to source code
#configure_file(config.h.in config.h)

# add the executable
add_executable()

target_link_libraries()

# add binary tree to search path for include files
target_include_directories()

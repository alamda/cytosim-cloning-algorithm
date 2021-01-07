#!/bin/bash

module unload gcc cmake
module load cmake/3.11.0 gcc/10.1.0

export CC=$(which gcc)
export CXX=$(which g++) 

#!/bin/bash

. ./cluster_setup.sh # same as source ./cluster_setup.shi

mdkdir build && cd build

ccmake .. 

make

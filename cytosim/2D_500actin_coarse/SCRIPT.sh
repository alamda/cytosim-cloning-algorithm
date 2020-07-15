#!/bin/bash

# use template to create individual config file
./preconfig.py config.cym.tpl

# copy *.cym files and necessary executables into individual directories and submit simulations with sbatch
./run_sims.sh

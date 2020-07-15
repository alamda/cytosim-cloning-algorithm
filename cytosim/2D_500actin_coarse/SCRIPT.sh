#!/bin/bash

# use template to create individual config file
./preconfig.py config.cym.tpl

# copy *.cym files into individual directories 
./run_sims.sh

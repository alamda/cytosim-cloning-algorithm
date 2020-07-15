#!/bin/bash

# Usage:
# ./continue.sh <slurm job name>

../../frametool objects.cmo 100 > objects.cmi

rm *.cmo *.err *.out

sbatch --job-name $1 cytosim.sbatch

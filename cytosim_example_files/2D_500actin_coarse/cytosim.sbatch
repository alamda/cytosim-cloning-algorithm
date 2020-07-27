#!/bin/bash
#SBATCH --job-name=cytosim
#SBATCH --output=./%j.out
#SBATCH --error=./%j.err
#SBATCH --account=pi-svaikunt
#SBATCH --time=24:00:00
#SBATCH --partition=broadwl
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=20
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-user=alexandral@uchicago.edu

#module load lammps/17Nov2016+intelmpi-5.1+intel-16.0
module load gcc

export OMP_NUM_THREADS=1 # multithreading

./sim config****.cym

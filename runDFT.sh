#!/bin/tcsh
#PBS -q class
#PBS -l nodes=1:sixcore
#PBS -l walltime=00:30:00
#PBS -N Poojan
# The below chnages the working directory to the location of
# your testmpi program
cd AutoCorelation-master
# The below tells MPI to run your jobs on 16 processors
time ./main.o



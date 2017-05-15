# CPAR_2 (Sieve of Eratosthenes)
Parallel Computing (CPAR) Repository for the second project. The primary goal of this project was to analyze the different algorithms, match them against each other and try and discuss the results. All of this data and analysis can be found in the report. Also, you may find some limitations in running the programs, depending on the specifications of your computer. It contains three primary modes to run:

## Sequential Algorithm
The original implementation with some constraints, as it isn't stored a list with all the numbers, but a vector containing booleans (in which the index is the number associated). 

## Parallel Algorithm with Shared Memory
This algorithm was implemented using OpenMP.

## Parallel Algorithm with Distributed Memory
This algorithm was implemented using MPI.

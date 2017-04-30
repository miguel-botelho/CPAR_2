#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <math.h>

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))



int main(int argc, char *argv[])
{
    int rank,size;

    /* Start up MPI */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    long long exponent = atol(argv[1]);
	if (exponent < 1) {
		printf("Invalid input: 2^N must equal or superior to 1\n");
		return 1;
	}

	// new_n = 2^n
	long long n = pow(2,exponent);

    struct timespec start, finish;
	double time_elapsed;

	if (rank == 0) {
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

    long long block_size = BLOCK_SIZE(rank, n-1, size);
	long long block_low = 2 + BLOCK_LOW(rank, n-1, size);
	long long block_high = 2 + BLOCK_HIGH(rank, n-1, size);



	bool * primes = new bool[block_size];
	memset(primes, true, block_size);

	long long k = 2;
	long long j;




    MPI_Finalize();
    return 0;
}

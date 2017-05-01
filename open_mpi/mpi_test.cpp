#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <math.h>

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))


using namespace std;
int totalPrimes(int size,bool* primes);

int main(int argc, char *argv[])
{
    int rank,size,len,root=0;

    /* Start up MPI */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char hostname[MPI_MAX_PROCESSOR_NAME];


    //cout << "Process "<< rank << " of "<< size<<endl;


    long long exponent = atol(argv[1]);
	  if (exponent < 1) {
		    printf("Invalid input: 2^N must equal or superior to 1\n");
		    return 1;
	  }

	// n = 2^exponent
	long long n = pow(2,exponent);
  struct timespec start, finish;
	double time_elapsed;

	if (rank == root) {
    cout << "Primes from 2 to "<<n<< endl;
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

  long long block_size = BLOCK_SIZE(rank, n-1, size);
	long long block_low = 2 + BLOCK_LOW(rank, n-1, size);
	long long block_high = 2 + BLOCK_HIGH(rank, n-1, size);

	bool * primes = new bool[block_size];
	memset(primes, true, block_size);
	long long k = 2;
	long long j;
  MPI_Get_processor_name(hostname, &len);


  cout << "PROCESSOR: "<<hostname<<"Process "<< rank << " of "<< size<<" block_low--> "<<block_low<<" block_high--> "<<block_high<<endl;

  //cout << "PRIMES-> "<< totalPrimes((int)block_size,primes)<<endl;


  while (k*k <= n) {

  		if (k*k < block_low) {
  			// Antes
  			if (block_low % k == 0)
  				j = block_low;
  			else
  				j = block_low + (k - (block_low % k));

  		} else {
  			j = k*k;
  		}

  		// Mark all multiples of k between k*k and n:
  		for (long long i = j; i <= block_high; i += k) {
  			primes[i - block_low] = false;
  		}


  		// Set k as the smallest urmarked number > k:
  		if (rank == root) {

  			for(long long i = k + 1; i < block_high; i++) {
  				if (primes[i - block_low]) {
  					k = i;
  					break;
  				}
  			}
  		}

  		MPI_Bcast(&k, 1, MPI_INT, root, MPI_COMM_WORLD);
  	}

  	int total_primes = 0;
  	int block_primes = totalPrimes(block_size,primes);

  	MPI_Reduce(&block_primes, &total_primes, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);


  	if (rank == root) {
  		clock_gettime(CLOCK_MONOTONIC, &finish);
  		time_elapsed = (finish.tv_sec - start.tv_sec);
  		time_elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  		cout << "2," << exponent << "," << size << ",0," << total_primes << "," << time_elapsed << endl;
  	}

  delete [] primes;



  MPI_Finalize();
  return 0;
}

int totalPrimes(int size,bool* primes){
  int res = 0;
  for(int i = 0; i < size; i++){
    if(primes[i]== true)
      res++;
  }
  return res;
}

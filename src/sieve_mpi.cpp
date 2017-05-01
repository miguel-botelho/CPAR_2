#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <math.h>
#include <papi.h>

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))


using namespace std;
int totalPrimes(int size,bool* primes);
void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}

int main(int argc, char *argv[])
{
    int rank,size,len,root=0;

    /* Start PAPI */
    bool* result;

  	int EventSet = PAPI_NULL;
    long long values[2];
    int ret;

  	ret = PAPI_library_init( PAPI_VER_CURRENT );
  	if ( ret != PAPI_VER_CURRENT )
  		std::cout << "FAIL" << endl;


  	ret = PAPI_create_eventset(&EventSet);
  	if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


  	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
  	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


  	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
  	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;

    ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;


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

  while (k*k <= n) {

  		if (k*k < block_low) {
  			if (block_low % k == 0)
  				j = block_low;
  			else
  				j = block_low + (k - (block_low % k));

  		} else {
  			j = k*k;
  		}

  		for (long long i = j; i <= block_high; i += k) {
  			primes[i - block_low] = false;
  		}

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
  		cout << "2^" << exponent << " time_elapsed--> " << time_elapsed << endl;

      ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
  		printf("L1 DCM: %lld \n",values[0]);
  		printf("L2 DCM: %lld \n",values[1]);
  		ret = PAPI_reset( EventSet );
  		if ( ret != PAPI_OK )
  			std::cout << "FAIL reset" << endl;

      ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
    	if ( ret != PAPI_OK )
    		std::cout << "FAIL remove event" << endl;

    	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
    	if ( ret != PAPI_OK )
    		std::cout << "FAIL remove event" << endl;

    	ret = PAPI_destroy_eventset( &EventSet );
    	if ( ret != PAPI_OK )
    		std::cout << "FAIL destroy" << endl;

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

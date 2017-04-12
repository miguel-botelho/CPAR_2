#include <papi.h>
#include <limits.h>
#include "sieve_of_eratosthenes.h"
using namespace std;

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


int main (int argc, char *argv[])
{
	int prime, realPrime, nthreads;
	int op;
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


	op=1;
	do {
		cout << endl << "1. Sequential" << endl;
		cout << "2. Parallel with OpenMP" << endl;
		cout << "3. Parallel with MPI" << endl;
		cout << "4. Parallel with MPI (Shared Version)" << endl;
		cout << "0. Exit" << endl;
		cout << "Selection?: ";
		cin >> op;
		if (op == 0)
			break;
		cout << "Prime numbers until: ";
   		cin >> prime;

		/*if (result == NULL) {
			cout << "Error allocating memory\n";
			exit(-1);
		}
    */
		//vector<int> result2 (;
		// Start counting
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;

		switch (op){
			case 1:
				SieveOfEratosthenes(prime);
				break;
			case 2:
				cout << "Number of threads: ";
				cin >> nthreads;
				SieveOfEratosthenesOpenMP(prime, nthreads);
				break;
			case 3:
				//result = SieveOfEratosthenesMPI(prime);
				break;
			case 4:
				//result = SieveOfEratosthenesMPIShared(prime);
				break;
		}

		ret = PAPI_stop(EventSet, values);
		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
		printf("L1 DCM: %lld \n",values[0]);
		printf("L2 DCM: %lld \n",values[1]);

    // start trolhice
    //std::vector<bool>().swap(numbers);
    //numbers.clear();
    //numbers.shrink_to_fit();
    // finish trolhice

		// fazer print dos primos
		/*
		for (int i=0;i<realPrime;i++)
        	if (result[i]!=-1)
				printf("%lld  ; ",result[i]);
		*/

		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl;

	}while (op != 0);

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

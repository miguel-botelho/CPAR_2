#include "sieve_of_eratosthenes.h"
using namespace std;

void SieveOfEratosthenes(int prime){
	SYSTEMTIME Time1, Time2;
	char st[100];
	long long realNumber = pow(2, prime);
	long long sqrtRealNumber = sqrt(realNumber);
	vector<bool> numbers(realNumber-1, true);

  Time1 = clock();

  /*sieve the non-primes*/
	for (long long i = 2; i <= sqrtRealNumber; i++) {
		if (numbers[i]) {
			for (long long j = i * i; j <= realNumber; j = j + i)
				numbers[j] = false;
		}
	}

	/*
	for (int k = 2;k < realNumber; k++)
      if (numbers[k])
          printf("%d\n", k);
	*/

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;
}
// instead of i*i <= lastNumber we write i <= lastNumberSquareRoot to help OpenMP
void SieveOfEratosthenesOpenMP(int prime, int nthreads) {
		long long realNumber = pow(2, prime);
    long long i,j;
		long long sqrtRealNumber = sqrt(realNumber);
    double inicialTime = omp_get_wtime();
    double finalTime;
		vector<bool> numbers(realNumber-1, true);

    /*sieve the non-primes*/
    #pragma omp parallel for schedule(dynamic) num_threads(nthreads)
		for (i = 2; i <= sqrtRealNumber; i++) {
			if (numbers[i]) {
				for (j = i * 2; j <= realNumber; j = j + i)
					numbers[j] = false;
			}
		}

    finalTime = omp_get_wtime();
    cout << "Time: " << finalTime - inicialTime << " seconds\n";
}

#include "sieve_of_eratosthenes.h"
using namespace std;

void SieveOfEratosthenes(int prime, char* numbers){

	SYSTEMTIME Time1, Time2;
	char st[100];
    long long k = 2;

	long long realNumber = pow(2, prime);

    Time1 = clock();

    /*fill the array with natural numbers*/
    for (long long i=0;i<realNumber;i++){
        numbers[i]=false;
    }

    /*sieve the non-primes*/

    while (k * k <= realNumber) {
        for (long long j=k*k;j<realNumber;j = j + k)
            numbers[j]=true;

        for (long long j=k+1;j <= realNumber; j++) {
            if (numbers[j] == false) {
                k = j;
                j = realNumber;
            }
        }
    }

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;
}

void SieveOfEratosthenesOpenMP(int prime, int nthreads, char* numbers) {
	long long realNumber = pow(2, prime);
    
    long long k = 2;
    double inicialTime = omp_get_wtime();
    double finalTime;

    /*fill the array with natural numbers*/
    #pragma omp target teams distribute parallel for map(from:numbers[0:realNumber])
    for (long long i=0;i<realNumber;i++){
        numbers[i]=false;
    }

    /*sieve the non-primes*/

    while (k * k <= realNumber) {
        #pragma omp parallel for private(j) num_threads(nthreads)
        for (long long j=k*k;j<realNumber;j = j + k)
            numbers[j]=true;

        for (long long j=k+1;j <= realNumber; j++) {
            if (numbers[j] == false) {
                k = j;
                j = realNumber;
            }
        }
    }
    
    finalTime = omp_get_wtime();
    cout << "Time: " << finalTime - inicialTime << " seconds\n";
}

long long* SieveOfEratosthenesMPI(int prime) {
	long long realNumber = pow(2, prime);
    long long *numbers = (long long *)malloc(realNumber * sizeof(long long));

    /*fill the array with natural numbers*/
    for (long long i=0;i<realNumber;i++){
        numbers[i]=i+2;
    }

    /*sieve the non-primes*/
    for (long long i=0;i<realNumber;i++){
        if (numbers[i]!=-1){
            for (long long j=2*numbers[i]-2;j<realNumber;j+=numbers[i])
                numbers[j]=-1;
        }
    }

	return numbers;
}

long long* SieveOfEratosthenesMPIShared(int prime) {
	long long realNumber = pow(2, prime);
    long long *numbers = (long long *)malloc(realNumber * sizeof(long long));

    /*fill the array with natural numbers*/
    for (long long i=0;i<realNumber;i++){
        numbers[i]=i+2;
    }

    /*sieve the non-primes*/
    for (long long i=0;i<realNumber;i++){
        if (numbers[i]!=-1){
            for (long long j=2*numbers[i]-2;j<realNumber;j+=numbers[i])
                numbers[j]=-1;
        }
    }

	return numbers;
}
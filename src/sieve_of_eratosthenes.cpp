#include "sieve_of_eratosthenes.h"
using namespace std;


long long* SieveOfEratosthenes(int prime){

	SYSTEMTIME Time1, Time2;
	char st[100];

	long long realNumber = pow(2, prime);
    fprintf(stderr, "oi\n");
    long long *numbers = (long long *)malloc(realNumber * sizeof(long long));

    Time1 = clock();

    /*fill the array with natural numbers*/
    for (long long i=0;i<realNumber;i++){
        numbers[i]=i+2;
    }

    fprintf(stderr, "oi2\n");
    /*sieve the non-primes*/
    for (long long i=0;i<realNumber;i++){
        if (numbers[i]!=-1){
            for (long long j=2*numbers[i]-2;j<realNumber;j+=numbers[i])
                numbers[j]=-1;
        }
    }

	Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	return numbers;
}

long long* SieveOfEratosthenesOpenMP(int prime) {
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
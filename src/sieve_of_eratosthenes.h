#ifndef __SIEVE_H
#define __SIEVE_H

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <omp.h>


#define SYSTEMTIME clock_t

void SieveOfEratosthenes(int prime, char* numbers);
void SieveOfEratosthenesOpenMP(int prime, int nthreads, char* numbers);
long long* SieveOfEratosthenesMPI(int prime);
long long* SieveOfEratosthenesMPIShared(int prime);

#endif
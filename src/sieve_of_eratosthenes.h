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

long long* SieveOfEratosthenes(int prime);
long long* SieveOfEratosthenesOpenMP(int prime);
long long* SieveOfEratosthenesMPI(int prime);
long long* SieveOfEratosthenesMPIShared(int prime);

#endif
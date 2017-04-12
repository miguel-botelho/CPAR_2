all: compiler

compiler: main.cpp
	mkdir -p ../bin
	g++ -O2 main.cpp sieve_of_eratosthenes.cpp -lpapi -fopenmp -o ../bin/sieve

clean:
	rm -rf *o *d ./bin/sieve

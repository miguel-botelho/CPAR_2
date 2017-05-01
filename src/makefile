all: compiler

compiler: main.cpp
	mkdir -p ../bin
	g++ -O2 main.cpp sieve_of_eratosthenes.cpp -lpapi -fopenmp -o ../bin/sieve
	mpiCC.openmpi sieve_mpi.cpp -lpapi -o sieve_mpi
	mpiCC.openmpi sieve_mpi_mp.cpp -lpapi -fopenmp -o sieve_mpi_mp
	scp sieve_mpi up201304828@192.168.108.58:
	scp sieve_mpi_mp up201304828@192.168.108.58:
	#scp sieve_mpi up201303095@192.168.108.60:
	#scp sieve_mpi_mp up201303095@192.168.108.60:
	#scp sieve_mpi up201303567@192.168.108.59:
	#scp sieve_mpi_mp up201303567@192.168.108.59:

clean:
	rm -rf *o *d ./bin/sieve

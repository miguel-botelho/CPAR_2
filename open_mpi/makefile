all: prog_cpp

prog_cpp:
	mpiCC.openmpi -o sieve_mpi sieve_mpi.cpp -lpapi
	mpiCC.openmpi -o sieve_mpi_mp sieve_mpi_mp.cpp -lpapi
	scp sieve_mpi up201304828@192.168.108.58:
	scp sieve_mpi_mp up201304828@192.168.108.58:
	scp sieve_mpi up201303095@192.168.108.60:
	scp sieve_mpi_mp up201303095@192.168.108.60:
	scp sieve_mpi up201303567@192.168.108.59:
	scp sieve_mpi_mp up201303567@192.168.108.59:
clean:
	\rm *.o *.class

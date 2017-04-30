CFLAGS=-std=c++11

all: prog_cpp

prog_cpp:
	mpiCC mpi_test.cpp -o mpi_test
	scp mpi_test up201304828@192.168.108.58:
clean:
	\rm *.o *.class
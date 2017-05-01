all: prog_cpp

prog_cpp:
	mpiCC.openmpi -o mpi_test mpi_test.cpp
	scp mpi_test up201304828@192.168.108.58:
	scp mpi_test up201303095@192.168.108.60:
	scp mpi_test up201303567@192.168.108.59:
clean:
	\rm *.o *.class

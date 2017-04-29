EXECS=mpi_test
MPICC?=mpicc

call: ${EXECS}

mpi_test: mpi_test.c
	${MPICC} -o mpi_test mpi_test.c
	scp mpi_test up201304828@192.168.108.58:

clean:rm ${EXECS}

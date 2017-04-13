#include <stdio.h>
#include "mpi.h"

int main( int argc, char **argv)
{
   int rank, size, erro;
   float *v1, *v2, *sv1, *sv2;
   int k, j, nelementos, my_k, maisum;
   float mysoma, soma;
    
   MPI_Init( &argc, &argv );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    
    
   if (rank == 0)
   {
   	printf("Tamanho dos vectores ? ");
   	scanf("%d", &k);
   	maisum = (k % size)==0 ? 0 : 1;
   	nelementos = ((k/size)+maisum)*size;
   	v1 = new float[nelementos];
   	v2 = new float[nelementos];

   	for(j=0; j<k; j++)
   	{
   		v1[j]=j;
   		v2[j]=1;
   	}
	for(j=k; j<nelementos; j++)
   	{
   		v1[j]=0;
   		v2[j]=0;
   	}
   }

	// broadcast de k a todos os processos
    //MPI_Bcast();
   
   // reservar espaco para os dados, o ultimo processador podera ficar com zeros no fim
	maisum = (k % size)==0 ? 0 : 1;
	my_k = (k/size)+maisum;
	sv1 = new float[my_k];
	sv2 = new float[my_k];

	// distribui os dados
	//erro = MPI_Scatter();
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    

	//erro = MPI_Scatter();
	printf("processo %d recebeu %d elementos, erro=%d\n",rank, my_k, erro);    
    
  
   // calcula produto interno
   mysoma = 0.0;
   for(j=0; j<my_k; j++)
   		mysoma += sv1[j]*sv2[j];
   	
   // processo 0 obtem resultado
   //erro = MPI_Reduce(); 
   	
   if (rank == 0)
   {	printf("Produto interno = %.1f\n", soma);
		delete [] v1;
		delete [] v2;
   }
   delete [] sv1;
   delete [] sv2;
   	
   MPI_Finalize();
    
   return 0;
}


/*#include <stdio.h>
#include "mpi.h"
int main( int argc,char **argv )
{ 
	int rank, value, size;
 	MPI_Status status;
 
 	MPI_Init( &argc, &argv );

 	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
 	MPI_Comm_size( MPI_COMM_WORLD, &size );
 	
 	do {
		if (rank == 0) {
 			scanf( "%d", &value );
 			MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
		}
		else {
 			MPI_Recv( &value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status );
 			if (rank < size - 1)
				MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
		}
		printf( "Process %d got %d\n", rank, value );
 	} while (value >= 0);
 	
 	MPI_Finalize( );
 	return 0;
}*/
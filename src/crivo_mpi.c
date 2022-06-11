#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *gerar_vetor(int n);
void imprimir_vetor(int *vetor, int n);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    time_t t;
    srand(time(NULL)*rank);
    
    /*
    INICIO
    */


    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

int *gerar_vetor(int n){
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i = 2; i < n; i++){
        vetor[i] = 1;
    }
    return vetor;
}

void imprimir_vetor(int *vetor, int n){
   for (int i = 1; i <= n; i++){
      if(vetor[i] == 1){
         printf("%d\n", i);
      }
   }
}
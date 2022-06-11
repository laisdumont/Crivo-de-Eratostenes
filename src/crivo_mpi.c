#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int *gerar_vetor(int n, int r);
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
    int i, j, N, raizN, tam_vet, x = 0; 
    int *v, *primos;
    
    primos = (int *)malloc(sizeof(int) * N);

    printf("\nValor de N: ");
    scanf("%d", &N);

    raizN = sqrt(N);
    tam_vet = N/rank;
    v = gerar_vetor(tam_vet, rank);

    /*
    INICIO
    */
    do{
        i = 2;

        if(rank == 0 && v[i] == 1){
            x = 1;
        } else{
            x = 0;
        }

        MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);

        if(x == 1){
            if(rank == 0){
                for(j = i+i; j <= N; j+=i){
                    v[j] = 0;
                }
            } else{
                for(j = 0; j <= N; j++){
                    if(j%i == 0){
                        v[j] = 0;
                    }
                }
            }
        }

        i++;

    } while(i <= raizN);

    MPI_Gather(&v, 1, MPI_INT, primos, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /*
    FIM
    */
    if(rank == 0){
        imprimir_vetor(primos, N);
    }
    
    MPI_Finalize();
    return 0;
}

int *gerar_vetor(int n, int r){
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);

    if(r == 0){
        for (i = 2; i < n; i++){
            vetor[i] = 1;
        }
    } else{
        for (i = n * r; i < n; i++){
            vetor[i] = 1;
        }
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
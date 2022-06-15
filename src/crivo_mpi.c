#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100000000

int *gerar_vetor(int n, int r);
void imprimir_vetor(int *vetor, int n);

    int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    /*
    INICIO
    */

    int i = 2, j, raizN, tam_vet, ponto = 0; 
    int *v, *primos;
    double inicio, fim;

    inicio = MPI_Wtime();

    raizN = sqrt(N);
    tam_vet = (int)(N/nprocs);
    v = gerar_vetor(tam_vet, rank);

    while(i <= raizN){
        if(rank == 0 && v[i] == 1){
            ponto = 1;
        } else{
            ponto = 0;
        }

        MPI_Bcast(&ponto, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if(ponto == 1){
            if(rank == 0){
                for(j = i+i; j < tam_vet; j+=i){
                    v[j] = 0;
                }
            } else{
                int passo;

                for(j = 0; j < tam_vet; j++){
                    if((j+(rank*tam_vet))%i == 0){
                        passo = j;
                        break;
                    }
                }

                for(j = passo; j < tam_vet; j+=i){
                    v[j] = 0;
                }
            }
        }

        i++;

    }

    if(rank == 0){
        primos = (int *)malloc(sizeof(int) * N);
    }

    MPI_Gather(v, tam_vet, MPI_INT, primos, tam_vet, MPI_INT, 0, MPI_COMM_WORLD);

    fim = MPI_Wtime();

    /*
    FIM
    */

    if(rank == 0){
        printf("\nTempo final = %f\n", fim-inicio);
        // imprimir_vetor(primos, N);
    }
    

    MPI_Finalize();

    return 0;
}

int *gerar_vetor(int n, int r){
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);

        for (i = 2; i < n; i++){
            if(r == 0 && i < 2){
                vetor[i] = 0;
            }
            vetor[i] = 1;
        }

    return vetor;
}

void imprimir_vetor(int *vetor, int n){
   for (int i = 0; i < n; i++){
      if(vetor[i] == 1){
         printf("%d\n", i);
      }
   }
}

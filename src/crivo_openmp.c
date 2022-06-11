#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *gerar_vetor(int n);
void imprimir_vetor(int *vetor, int n);

int main (void)
{
  int i, j, N, raizN; 
  int *v;
    
  printf("\nValor de N: ");
  scanf("%d", &N);

  v = gerar_vetor(N);
   
  raizN = sqrt(N);

  // PARALELIZAR COM OPENMP
   for (i = 2; i <= raizN; i++){
      if (v[i] == 1){
         for (j = i+i; j <= N; j+=i){
            v[j] = 0;
         }
      }
   }
  // ATÉ AQUI

  imprimir_vetor(v, N);

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
#include <stdio.h>

#define TAM 100

void leVetor (int n, int vetor[])
{
    int i;

    for(i = 0; i < n; i++)
        scanf("%d", &vetor[i]);
}

void somaVetor (int n, int vetorA[], int vetorB [], int vetorR[])
{
    for(int i = 0; i < n; i++)
        vetorR[i] = vetorA[i] + vetorB[i];
}

int imprimeVetor (int n, int vetorR [])
{
    for(int i = 0; i < n; i++)
        printf("%d ", vetorR[i]);
    printf("\n");
    return 0;
}

int main ()
{
    int vetorA[TAM], vetorB[TAM], vetorR[TAM];
    int n;

    scanf("%d", &n);
    leVetor(n, vetorA);
    leVetor(n, vetorB);
    somaVetor(n, vetorA, vetorB, vetorR);
    imprimeVetor(n, vetorR);
    return 0;
}
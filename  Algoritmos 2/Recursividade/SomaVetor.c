#include <stdio.h>

#define TAM 5

void leVetor(int v[])
{
    for(int i = 0; i < TAM; i++)
    {
        scanf("%d", &v[i]);
    }
}

int somavetor(int v[])
{
    int soma = 0;
    for(int j = 0; j < TAM; j++)
    {
        soma += v[j];
    }
    return soma;
}

int main ()
{
    int vetor[TAM];

    leVetor(vetor);
    somavetor(vetor);
    printf("%d\n", somavetor(vetor));
    return 0;
}
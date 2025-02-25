#include <stdio.h>

#define TAM 5

void leVetor(int v[])
{
    for(int i = 0; i < TAM; i++)
    {
        scanf("%d", &v[i]);
    }
}

int somavetor(int v[], int n)
{
    if (n == 0)
        return 0;
    else
        return v[n - 1] + somavetor(v, n - 1);
}

int main ()
{
    int vetor[TAM];

    leVetor(vetor);
    printf("%d\n", somavetor(vetor, TAM));
    return 0;
}
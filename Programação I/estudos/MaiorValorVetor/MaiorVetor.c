#include <stdio.h>

#define TAM 100

int maiorvalor (int n, int vetor[])
{
    int maioratual;

    maioratual = vetor[0];
    for(int i = 0; i < n; i++)
    {
        if(maioratual < vetor[i])
            maioratual = vetor[i];
    }
    return maioratual;
}

void leVetor (int n, int vetor[])
{
    int i;

    for(i = 0; i < n; i++)
        scanf("%d", &vetor[i]);
}

int main ()
{
    int vetor [TAM];
    int n;

    scanf("%d", &n);
    leVetor(n, vetor);
    printf("%d\n", maiorvalor(n, vetor));
    return 0;
}
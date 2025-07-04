#include <stdio.h>

#define TAM 100

void leVetor (int n, int vetor[])
{
    int i;

    for(i = 0; i < n; i++)
        scanf("%d", &vetor[i]);
}

void ordenaVetor (int n, int vetor[])
{
    int auxiliar;

    for(int j = 0; j < n - 1; j++)
    {
        for(int h = 0; h < n - j - 1; h++)
        {
                if (vetor[h] > vetor[h + 1])
                {
                        auxiliar = vetor[h];
                        vetor[h] = vetor[h + 1];
                        vetor[h + 1] = auxiliar;
                }
        }
    }
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
    int n; 
    int vetor[TAM];

    scanf("%d", &n);
    leVetor(n, vetor);
    ordenaVetor(n, vetor);
    imprimeVetor(n, vetor);
    return 0;
}
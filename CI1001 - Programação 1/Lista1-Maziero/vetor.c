#include <stdio.h>

#define MAX 1000

int main ()
{
    int n, num;
    int vetor[MAX];

    /*carrega o vetor*/
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        vetor[i] = num;
    }

    /*inverte o vetor*/
    int auxiliar = 0;
    for(int j = 0; j < n/2; j++)
    {
        auxiliar = vetor[j];
        vetor[j] = vetor[n - j - 1];
        vetor[n - j -1] = auxiliar;
    }

    /*imprime o vetor*/
    for(int k = 0; k < n; k++)
    {
        printf("%d ", vetor[k]);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>

#define MAX 1000

int main ()
{
    int n, menor, aux;
    int vetor[MAX];

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &vetor[i]);
    }

    for(int j = 0; j < n - 1; j++)
    {
        menor = j; /*assume que o menor valor está na posição j*/
        for(int h = j + 1; h < n; h++)
        {
            printf("j: %d  -  h: %d\n", j, h);
            if (vetor[h] < vetor[menor])
            {
                menor = h;
            }    
        }
        if(menor != j)
        {
            aux = vetor[j];
            vetor[j] = vetor[menor];
            vetor[menor] = aux;
        }
    }
    for(int k = 0; k < n; k++)
    {
        printf("%d ", vetor[k]);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>

#define MAX 1000

int main ()
{
    int vetor [MAX];
    int n, num, auxiliar;

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        vetor[i] = num;
    }

    for(int j = 0; j < n - 1; j++)
    {
        for(int h = 0; h < n - j - 1; h++)
        {
            printf("h: %d j: %d \n", h, j);
            if (vetor[h] > vetor[h + 1])
            {
                auxiliar = vetor[h];
                vetor[h] = vetor[h + 1];
                vetor[h + 1] = auxiliar;
            }
        }
    }
    for(int k = 0; k < n; k++)
    {
        printf("%d ", vetor[k]);
    }
    printf("\n");
    return 0;
}
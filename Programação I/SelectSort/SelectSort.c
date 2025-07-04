#include <stdio.h>

#define TAM 1000

void selectSort(int vetor[], int n) 
{
    int i, j, min, aux;

    for (i = 0; i < n - 1; i++) 
    { 
        min = i;
        for (j = i + 1; j < n; j++) 
        { 
            if (vetor[j] < vetor[min])
                min = j;
        }
        aux = vetor[min];
        vetor[min] = vetor[i];
        vetor[i] = aux;
    }
}

int main() 
{
    int vetor[TAM];
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &vetor[i]);

    selectSort(vetor, n);

    for (i = 0; i < n; i++) 
        printf("%d ", vetor[i]);

    return 0;
}

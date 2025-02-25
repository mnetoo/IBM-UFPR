#include <stdio.h>

#define TAM 10


// Função para trocar dois elementos
void trocar(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o vetor
int particionar(int vetor[], int inicio, int fim) 
{
    int pivo = vetor[inicio];
    int i = inicio + 1;
    int j = fim;

    while (i <= j) 
    {
        while (i <= fim && vetor[i] <= pivo) 
        i++;
        while (j > inicio && vetor[j] > pivo) 
        j--;

        if (i < j) 
            trocar(&vetor[i], &vetor[j]);
    }

    trocar(&vetor[inicio], &vetor[j]);
    return j;
}

// Função QuickSort
void quickSort(int vetor[], int inicio, int fim) 
{
    if (inicio < fim) 
    {
        int indicePivo = particionar(vetor, inicio, fim);
        quickSort(vetor, inicio, indicePivo - 1);
        quickSort(vetor, indicePivo + 1, fim);
    }
}



int main ()
{
    int v[TAM];

    printf("Digite os %d elementos do vetor: ", TAM);
    for (int i = 0; i < TAM; i++)
    {
        scanf("%d", &v[i]);
    }

    quickSort(v, 0, TAM - 1);
    printf("Vetor ordenado: ");
    for (int i = 0; i < TAM; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");



    return 0;
}
#include <stdio.h>

// Função que implementa o Merge Sort
void ordenar(int vetor[], int inicio, int fim) 
{
    if (inicio < fim) 
    {
        // Determina o ponto médio do vetor
        int meio = inicio + (fim - inicio) / 2;

        // Ordena a metade esquerda
        ordenar(vetor, inicio, meio);

        // Ordena a metade direita
        ordenar(vetor, meio + 1, fim);

        // Mescla as duas metades ordenadas
        int n1 = meio - inicio + 1; // Tamanho do subarray esquerdo
        int n2 = fim - meio;        // Tamanho do subarray direito

        int esquerda[n1], direita[n2];

        // Copia os elementos do vetor original para os subarrays
        for (int i = 0; i < n1; i++)
            esquerda[i] = vetor[inicio + i];
        for (int j = 0; j < n2; j++)
            direita[j] = vetor[meio + 1 + j];

        int i = 0, j = 0, k = inicio;

        // Mescla os elementos dos subarrays de volta no vetor original
        while (i < n1 && j < n2) 
        {
            if (esquerda[i] <= direita[j]) 
            {
                vetor[k] = esquerda[i];
                i++;
            } 
            else 
            {
                vetor[k] = direita[j];
                j++;
            }
            k++;
        }

        // Copia os elementos restantes do subarray esquerdo, se houver
        while (i < n1) 
        {
            vetor[k] = esquerda[i];
            i++;
            k++;
        }

        // Copia os elementos restantes do subarray direito, se houver
        while (j < n2) 
        {
            vetor[k] = direita[j];
            j++;
            k++;
        }
    }
}

int main() {
    int vetor[] = {38, 27, 43, 3, 9, 82, 10};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");

    // Chamada da função de ordenação
    ordenar(vetor, 0, tamanho - 1);

    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");

    return 0;
}

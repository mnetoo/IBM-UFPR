//                                      UTILIZANDO A SEQUÊNCIA DE HIBBARD


// Ordena o vetor utilizando o método shellsort com a sequência de Hibbard
void shellSortHibbard(int vetor[], int n) 
{
    int k = 1;
    // Calcula o maior gap de Hibbard que seja menor que o tamanho do vetor
    while ((1 << k) - 1 < n) {
        k++;
    }
    k--;

    for (int gap = (1 << k) - 1; gap > 0; k--, gap = (1 << k) - 1) {
        // Ordenação com o gap atual
        for (int i = gap; i < n; i++) {
            int temp = vetor[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                //contagemComparacoes++; // Incrementa a contagem de comparações
                if (vetor[j - gap] > temp) {
                    vetor[j] = vetor[j - gap];
                } else {
                    break; // Se não for maior, sai do loop
                }
            }
            vetor[j] = temp; // Move o elemento para a posição correta
            //contagemTrocas++; // Incrementa a contagem de trocas
        }
    }
}
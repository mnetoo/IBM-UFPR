/*================================================ [SHELL SORT] ===========================================================*/


//                                      UTILIZANDO A SEQUÊNCIA DE KNUTH


//Ordena o vetor utilizando o método shellsort com a sequência de Knuth
void shellSortKnuth(int vetor[], int n) 
{
    int gap = 1;
    // Calcula o maior gap de Knuth que seja menor que o tamanho do vetor
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    for (; gap > 0; gap = (gap - 1) / 3) {
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
            if (j != i) { // Se houve troca
                vetor[j] = temp;
                //contagemTrocas++; // Incrementa a contagem de trocas
            }
        }
    }
}


/*===========================================================================================================*/
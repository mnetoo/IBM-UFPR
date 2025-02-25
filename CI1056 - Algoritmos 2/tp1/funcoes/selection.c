//                                      UTILIZANDO O SELECTION SORT


// Ordena o vetor utilizando o método Selection Sort
void selectionSort(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;  // Assume que o primeiro elemento não ordenado é o menor
        for (int j = i + 1; j < n; j++) {
            //contagemComparacoes++;  // Incrementa a contagem de comparações
            // Atualiza o índice do menor elemento encontrado
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento não ordenado
        if (indiceMenor != i) {
            trocar(&vetor[i], &vetor[indiceMenor]);  // Chama a função de troca
        }
    }
}
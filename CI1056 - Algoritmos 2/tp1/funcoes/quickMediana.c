//                              UTILIZANDO A MEDIANA DE TRÊS ELEMENTOS DO VETOR

// Escolhe o pivô como a mediana de três (primeiro, meio e último elementos)
int medianaDeTres(int vetor[], int inicio, int fim) 
{
    int meio = (inicio + fim) / 2;

    // Ordena inicio, meio e fim para obter a mediana
    if (vetor[inicio] > vetor[meio]) trocar(&vetor[inicio], &vetor[meio]);
    if (vetor[inicio] > vetor[fim]) trocar(&vetor[inicio], &vetor[fim]);
    if (vetor[meio] > vetor[fim]) trocar(&vetor[meio], &vetor[fim]);

    // Coloca a mediana no final, onde será usada como pivô
    trocar(&vetor[meio], &vetor[fim]);
    return vetor[fim];
}


//  Particiona o vetor de forma que os elementos menores que o pivô fiquem à esquerda e os maiores à direita
int particionarMedianaDeTres(int vetor[], int inicio, int fim) 
{
    int pivo = medianaDeTres(vetor, inicio, fim);  // Escolhe o pivô como a mediana de três
    int indiceMenor = inicio - 1;

    for (int i = inicio; i < fim; i++) 
    {
        //contagemComparacoes++;
        if (vetor[i] < pivo) 
        {
            indiceMenor++;
            trocar(&vetor[indiceMenor], &vetor[i]);
        }
    }
    trocar(&vetor[indiceMenor + 1], &vetor[fim]);
    return indiceMenor + 1;
}


// Ordena o vetor utilizando o método quicksort com a mediana de três como pivô
void quickSortMedianaDeTres(int vetor[], int inicio, int fim) 
{
    if (inicio < fim) {
        int indicePivo = particionarMedianaDeTres(vetor, inicio, fim);
        quickSortMedianaDeTres(vetor, inicio, indicePivo - 1);
        quickSortMedianaDeTres(vetor, indicePivo + 1, fim);
    }
}
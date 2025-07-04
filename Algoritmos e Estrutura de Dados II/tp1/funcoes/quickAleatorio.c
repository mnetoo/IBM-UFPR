//                                UTILIZANDO UM ELEMENTO ALEATÓRIO DO VETOR COMO PIVÔ


// Função que particiona o vetor de forma que os elementos menores que o pivô fiquem à esquerda e os maiores à direita do pivô.
// O pivô é escolhido aleatoriamente.
int particionarAleatorio(int vetor[], int inicio, int fim) 
{
    // Escolhe um índice aleatório entre inicio e fim
    int indicePivoAleatorio = inicio + rand() % (fim - inicio + 1);
    
    // Troca o elemento aleatório com o Aleatório elemento para usá-lo como pivô
    trocar(&vetor[indicePivoAleatorio], &vetor[fim]);

    int pivo = vetor[fim];  // Define o pivô como o elemento agora na posição 'fim'
    int indiceMenor = inicio - 1;  // Inicializa o índice do menor elemento

    // Percorre o vetor do início até o penAleatório elemento (fim - 1), comparando cada elemento com o pivô
    for (int i = inicio; i < fim; i++) 
    {   
        contagemComparacoes++;  // Conta cada comparação feita entre o elemento e o pivô
        if (vetor[i] < pivo) {  // Se o elemento é menor que o pivô, ele deve ser movido para a esquerda
            indiceMenor++;  // Incrementa o índice do menor elemento
            trocar(&vetor[indiceMenor], &vetor[i]);  // Troca os elementos de posição
        }
    }

    // Coloca o pivô na posição correta, entre os elementos menores e maiores
    trocar(&vetor[indiceMenor + 1], &vetor[fim]);
    
    // Retorna o índice da posição final do pivô
    return indiceMenor + 1;
}


// Função que implementa o algoritmo de ordenação QuickSort utilizando um pivô aleatório
void quickSortAleatorio(int vetor[], int inicio, int fim) 
{
    // A recursão só continua se houver mais de um elemento a ser ordenado
    if (inicio < fim) {
        // Particiona o vetor e encontra o índice do pivô
        int indicePivo = particionarAleatorio(vetor, inicio, fim);
        
        // Ordena recursivamente os elementos à esquerda do pivô
        quickSortAleatorio(vetor, inicio, indicePivo - 1);
        
        // Ordena recursivamente os elementos à direita do pivô
        quickSortAleatorio(vetor, indicePivo + 1, fim);
    }
}
//                                       ALGORITMO DE BUSCA BINÁRIA


// Função de busca binária no vetor ordenado
int buscaBinaria(int vetor[], int tamanho, int elemento, int *contagemComparacoes) {
    int inicio = 0, fim = tamanho - 1;
    *contagemComparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*contagemComparacoes)++;

        if (vetor[meio] == elemento) {
            return meio;  // Retorna o índice onde o elemento foi encontrado
        }
        else if (vetor[meio] < elemento) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    return -1;  // Retorna -1 se o elemento não for encontrado
}

// Função para permitir consulta de elemento no vetor, com entrada ou número aleatório
void realizarBuscaBinaria(int vetor[], int tamanho) {
    int elemento, contagemComparacoes = 0, opcao;

    // Loop para garantir que o usuário escolha uma opção válida
    do {
        printf("Escolha uma opção para a busca binária:\n");
        printf("1 - Digitar o elemento a ser buscado\n");
        printf("2 - Gerar aleatoriamente o elemento a ser buscado\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao != 1 && opcao != 2) {
            printf("Opção inválida! Por favor, escolha 1 ou 2.\n");
        }
    } while (opcao != 1 && opcao != 2);

    if (opcao == 1) {
        printf("Digite o elemento a ser buscado: ");
        scanf("%d", &elemento);
    } else {
        elemento = rand() % (MAX_VAL + 1); // Gera número aleatório entre 0 e MAX_VAL
        printf("Elemento gerado aleatoriamente: %d\n", elemento);
    }

    // Realiza a busca binária no vetor ordenado
    int posicao = buscaBinaria(vetor, tamanho, elemento, &contagemComparacoes);

    // Exibe o resultado da busca
    if (posicao != -1) {
        printf("Elemento encontrado na posição: %d\n", posicao);
    } else {
        printf("Elemento não encontrado no vetor.\n");
    }
    printf("Número de comparações realizadas: %d\n", contagemComparacoes);
}


/*===========================================================================================================*/
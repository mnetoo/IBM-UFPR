/*====================================== [ALGORITMOS DE PESQUISA] =================================================*/


//                                    ALGORITMO DE BUSCA SEQUENCIAL


// Função para buscar um elemento sequencialmente no vetor e contar as comparações
int buscaSequencial(int vetor[], int tamanho, int elemento, int *contagemComparacoes) {
    *contagemComparacoes = 0; // Zera a contagem no início da busca

    for (int i = 0; i < tamanho; i++) {
        (*contagemComparacoes)++; // Incrementa a contagem a cada comparação
        if (vetor[i] == elemento) {
            return i; // Retorna o índice onde o elemento foi encontrado
        }
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}



// Escolhe entre um número digitado pelo usuário ou gerado aleatoriamente para busca
void realizarBuscaSequencial(int vetor[], int tamanho) {
    int opcao, elemento, posicao;
    int comparacoes;

    // Pergunta ao usuário se ele quer inserir um valor ou gerar um número aleatório
    do {
        printf("Escolha uma opção:\n");
        printf("1. Digitar um número para buscar\n");
        printf("2. Gerar um número aleatório para buscar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao != 1 && opcao != 2) {
            printf("Opção inválida! Por favor, escolha 1 ou 2.\n");
        }
    } while (opcao != 1 && opcao != 2);

    if (opcao == 1) {
        printf("Digite o número a ser buscado: ");
        scanf("%d", &elemento);
    } else {
        elemento = rand() % (MAX_VAL + 1); // Gera número aleatório entre 0 e MAX_VAL
        printf("Número gerado aleatoriamente para busca: %d\n", elemento);
    }

    // Realiza a busca sequencial no vetor original
    posicao = buscaSequencial(vetor, tamanho, elemento, &comparacoes);

    // Exibe o resultado da busca
    if (posicao != -1) {
        printf("Elemento %d encontrado na posição %d após %d comparações.\n", elemento, posicao, comparacoes);
    } else {
        printf("Elemento %d não encontrado no vetor após %d comparações.\n", elemento, comparacoes);
    }
}



/*===========================================================================================================*/
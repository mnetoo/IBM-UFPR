#include "hash.h"


int main(int argc, char *argv[]) 
{
    // Se foi passado o argumento -h, imprime informações e sai
    if (argc == 2 && strcmp(argv[1], "-h") == 0) 
    {
        printf("Nome: Marcus Sebastião Adriano Rocha Neto\n");
        printf("GRR: 20240710\n");
        printf("login: msarn24\n");
        return 0;
    }

    struct HashTable tabela;
    inicializa_hash(&tabela);

    char opcao;
    int valor;

    // Leitura dos opcaos i <valor> ou r <valor>
    while (scanf(" %c %d", &opcao, &valor) == 2) 
    {
        if (opcao == 'i') 
            inserir(&tabela, valor);

        else if (opcao == 'r')
            remover(&tabela, valor);

        else
            // opcao inválido
            printf("Opção desconhecida: %c\n", opcao);
    }

    // Imprime a tabela final
    imprimeHash(&tabela);

    return 0;
}
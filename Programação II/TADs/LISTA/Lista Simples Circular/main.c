#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"




int main()
{
    lista* list = criar_lista();

    // Insere valores na lista
    printf("Inserindo valores na lista:\n\n");

    printf("Inserindo valor 10\n");
    inserir_lista(list, 10);
    imprimir_lista(list);

    printf("Inserindo valor 20\n");
    inserir_lista(list, 20);
    imprimir_lista(list);

    printf("Inserindo valor 30\n");
    inserir_lista(list, 30);
    imprimir_lista(list);

    printf("Inserindo valor 40\n");
    inserir_lista(list, 40);
    imprimir_lista(list);

    printf("Inserindo valor 50\n");
    inserir_lista(list, 50);
    imprimir_lista(list);



    // Removendo um valor da lista
    printf("Removendo valores da lista:\n\n");

    int valor_removido;

    valor_removido = remover_lista(list); // Remove 10
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimir_lista(list);

    valor_removido = remover_lista(list); // Remove 20
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimir_lista(list);

    valor_removido = remover_lista(list); // Remove 30
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimir_lista(list);

    valor_removido = remover_lista(list); // Remove 40
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimir_lista(list);

    valor_removido = remover_lista(list); // Remove 50
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimir_lista(list);

    
    // Libera a memória alocada
    destruir_lista(list);

    return 0;
}
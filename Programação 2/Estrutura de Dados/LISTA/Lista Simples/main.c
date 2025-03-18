#include <stdio.h>
#include <stdlib.h>
#include "lista_simples.h"

int main() {
    lista *l = inicializa_lista();

    // Verifica se a lista foi inicializada corretamente
    verifica_lista(l);

    // Insere valores na lista
    printf("Inserindo valores na lista:\n\n");

    printf("Inserindo valor 10\n");
    insere_lista(l, 10);
    imprimindo_lista(l);

    printf("Inserindo valor 20\n");
    insere_lista(l, 20);
    imprimindo_lista(l);

    printf("Inserindo valor 30\n");
    insere_lista(l, 30);
    imprimindo_lista(l);

    printf("Inserindo valor 40\n");
    insere_lista(l, 40);
    imprimindo_lista(l);

    printf("Inserindo valor 50\n");
    insere_lista(l, 50);
    imprimindo_lista(l);

    // Removendo um valor da lista
    printf("Removendo valores da lista:\n\n");

    int valor_removido;

    valor_removido = remove_lista(l); // Remove 10
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimindo_lista(l);

    valor_removido = remove_lista(l); // Remove 20
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimindo_lista(l);

    valor_removido = remove_lista(l); // Remove 30
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimindo_lista(l);

    valor_removido = remove_lista(l); // Remove 40
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimindo_lista(l);

    valor_removido = remove_lista(l); // Remove 50
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);
    imprimindo_lista(l);

    valor_removido = remove_lista(l); // Lista vazia
    if (valor_removido != -1)
        printf("Valor removido: %d\n", valor_removido);

    // Libera a memória alocada
    free(l);

    return 0;
}
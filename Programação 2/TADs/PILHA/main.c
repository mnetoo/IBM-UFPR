#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"




int main() 
{
    int cap;
    pilha *p;

    printf("Digite a capacidade da pilha: \n");
    scanf("%d", &cap);

    if (cap > 0)
        p = criar_pilha(cap);
    else 
    {
        printf("Capacidade deve ser maior que zero!\n");
        return 0;
    }

    printf("\nInserindo na pilha...\n\n");

    printf("Inserindo valor 10:");
    inserir_elemento(p, 10);
    imprimir_pilha(p);

    printf("Inserindo valor 20:");
    inserir_elemento(p, 20);
    imprimir_pilha(p);

    printf("Inserindo valor 30:");
    inserir_elemento(p, 30);
    imprimir_pilha(p);

    printf("Inserindo valor 40:");
    inserir_elemento(p, 40);
    imprimir_pilha(p);

    printf("Inserindo valor 50:");
    inserir_elemento(p, 50);
    imprimir_pilha(p);


    printf("\nRetirando o topo da pilha...\n");
    retirar_elemento(p);
    imprimir_pilha(p);

    printf("\nImprimindo a capacidade da pilha...\n");
    cap = capacidade(p);
    printf("Capacidade: %d\n", cap);

    printf("\nImprimindo a tamanho da pilha...\n");
    int tam = tamanho_pilha(p);
    printf("Tamanho: %d\n", tam);

    printf("\nImprimindo o topo da pilha...\n");
    int topo = pilha_topo(p);
    printf("Topo: %d\n", topo);


    printf("\nRemovendo os elementos da pilha...\n");
    remover_elementos(p);
    imprimir_pilha(p);


    printf("\nDestruindo pilha...\n");
    destruir_pilha(p);


    return 0;
}
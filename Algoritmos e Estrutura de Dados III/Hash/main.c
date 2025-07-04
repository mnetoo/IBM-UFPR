#include <stdio.h>
#include <stdlib.h>
#include "hash.h"



int main() 
{
    // Inicializa tabela1 hash com NULL
    struct nodo* tabela1[M] = {NULL};
    // Inicializa tabela1 hash com NULL
    struct nodo* tabela2[M] = {NULL};

    // Inserções de exemplo
    inserir_h1(tabela1, 1);
    inserir_h1(tabela1, 2);
    inserir_h1(tabela1, 3);
    inserir_h1(tabela1, 4);
    inserir_h1(tabela1, 5);
    inserir_h1(tabela1, 6);
    inserir_h1(tabela1, 7);
    inserir_h1(tabela1, 8);
    inserir_h1(tabela1, 9);
    inserir_h1(tabela1, 10);
    inserir_h1(tabela1, 11);
    inserir_h1(tabela1, 12);
    inserir_h1(tabela1, 13);
    inserir_h1(tabela1, 14);
    inserir_h1(tabela1, 15);
    inserir_h1(tabela1, 16);

    // Inserções de exemplo
    inserir_h2(tabela2, 1);
    inserir_h2(tabela2, 2);
    inserir_h2(tabela2, 3);
    inserir_h2(tabela2, 4);
    inserir_h2(tabela2, 5);
    inserir_h2(tabela2, 6);
    inserir_h2(tabela2, 7);
    inserir_h2(tabela2, 8);
    inserir_h2(tabela2, 9);
    inserir_h2(tabela2, 10);
    inserir_h2(tabela2, 11);
    inserir_h2(tabela2, 12);
    inserir_h2(tabela2, 13);
    inserir_h2(tabela2, 14);
    inserir_h2(tabela2, 15);
    inserir_h2(tabela2, 16);


    imprimirTabela(tabela1);
    printf("\n\n");
    imprimirTabela(tabela2);

    liberarTabela(tabela1);
    liberarTabela(tabela2);

    return 0;
}
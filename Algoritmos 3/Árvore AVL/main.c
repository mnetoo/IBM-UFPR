#include <stdio.h>
#include "avl.h"

int main() 
{
    No* raiz = NULL;

    int valores[] = {30, 20, 10, 25, 40, 50, 22};
    int n = sizeof(valores) / sizeof(valores[0]);

    // Inserindo elementos na árvore
    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Árvore AVL (em-ordem): ");
    em_ordem(raiz);
    printf("\n");

    // Removendo um elemento
    raiz = remover(raiz, 25);
    printf("Após remover 25: ");
    em_ordem(raiz);
    printf("\n");

    liberar_arvore(raiz);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "Árvore.h"





int main() 
{
    struct nodo *raiz = NULL; // Começamos com uma árvore vazia

    // Inserindo elementos
    printf("\nInserindo elementos na árvore...\n");
    raiz = insere(raiz, 10);
    raiz = insere(raiz, 5);
    raiz = insere(raiz, 15);
    raiz = insere(raiz, 3);
    raiz = insere(raiz, 7);
    raiz = insere(raiz, 12);
    raiz = insere(raiz, 18);

    // Imprimindo a árvore em ordem
    printf("Árvore em ordem: ");
    em_ordem(raiz);
    printf("\n");

    // Imprimindo a árvore em ordem
    printf("Árvore em pré ordem: ");
    pre_ordem(raiz);
    printf("\n");

    // Imprimindo a árvore em pós ordem
    printf("Árvore em pós ordem: ");
    pos_ordem(raiz);
    printf("\n");



    printf("\nEncontrando o valor mínimo e máximo da árvore...\n");
    struct nodo *minimo = find_min(raiz);
    struct nodo *maximo = find_max(raiz);

    if (minimo != NULL)
        printf("Menor valor da árvore: %d\n", minimo->chave);
    if (maximo != NULL)
        printf("Maior valor da árvore: %d\n", maximo->chave);





    // Rotacionar à esquerda no nó 10
    printf("\nRotacionando à esquerda no nó 10...\n");
    struct nodo *nodo_10 = buscar(raiz, 10);
    if (nodo_10 != NULL) 
    {
        if (nodo_10 == raiz)
            raiz = rotacionar_esquerda(raiz);
        else
            rotacionar_esquerda(nodo_10);
        
        printf("Após rotação à esquerda: ");
        em_ordem(raiz);
        printf("\n");
    } 
    else
        printf("Nó com chave 10 não encontrado!\n");



    // Rotacionar à direita no nó raiz (após a rotação anterior)
    printf("\nRotacionando à direita no nó %d...\n", raiz->chave);

    // Verifica se a rotação é possível (raiz tem filho esquerdo?)
    if (raiz->esquerda != NULL) 
    {
        raiz = rotacionar_direita(raiz);
        printf("Após rotação à direita: ");
        em_ordem(raiz);  // Verifica o resultado
        printf("\n");
    } 
    else
        printf("Erro: Nó %d não tem filho esquerdo (rotação impossível)\n", raiz->chave);





    return 0;
}
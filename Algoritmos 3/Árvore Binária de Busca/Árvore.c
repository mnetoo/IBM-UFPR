#include <stdio.h>
#include <stdlib.h>





struct nodo 
{
    int chave;
    struct nodo *esquerda;
    struct nodo *direita;
    struct nodo *pai;
};


struct nodo* cria_nodo(int chave)
{
    struct nodo *n = (struct nodo*) malloc(sizeof(struct nodo));

    if (n == NULL)
    {
        fprintf(stderr, "Erro ao criar nodo!\n");
        return NULL;
    }

    n->chave = chave;
    n->esquerda = NULL;
    n->direita = NULL;
    n->pai = NULL;

    return n;
}


// Função para inserir um novo nó na árvore binária
struct nodo* binary(struct nodo *n, int chave)
{
    if (n == NULL)
        return cria_nodo(chave);

    if (chave < n->chave) 
    {
        n->esquerda = binary(n->esquerda, chave);
        n->esquerda->pai = n; // Atualiza o ponteiro do pai
    } 
    else if (chave > n->chave) 
    {
        n->direita = binary(n->direita, chave);
        n->direita->pai = n; // Atualiza o ponteiro do pai
    }

    return n;    
}


// Função para imprimir a árvore em ordem
void printTree(struct nodo *n)
{
    if (n == NULL)
        return;  // Corrigido o erro de ponto e vírgula

    printTree(n->esquerda);
    printf("%d ", n->chave);
    printTree(n->direita);
}


int main() 
{
    struct nodo *raiz = NULL; // Começamos com uma árvore vazia

    // Inserindo elementos
    raiz = binary(raiz, 10);
    raiz = binary(raiz, 5);
    raiz = binary(raiz, 15);
    raiz = binary(raiz, 3);
    raiz = binary(raiz, 7);
    raiz = binary(raiz, 12);
    raiz = binary(raiz, 18);

    // Imprimindo a árvore em ordem
    printf("Árvore em ordem: ");
    printTree(raiz);
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>




struct nodo
{
    int chave;
    struct nodo *esquerda;
    struct nodo *direita;
    struct nodo *pai;

};


struct arvore
{
    struct nodo *raiz;
};


struct nodo* cria_nodo(int chave)
{
    struct nodo *n = (struct nodo*) malloc(sizeof(struct nodo));

    n->chave = chave;
    n->esquerda = NULL;
    n->direita = NULL;
    n->pai = NULL;

    return n;
}

struct nodo* inserir(struct nodo *no, int chave)
{
    if (no == NULL)
        return cria_nodo(chave);

    if (chave < no->chave)
    {
        no->esquerda = inserir(no->esquerda, chave);
        no->esquerda->pai = no;
    }
    else if (chave > no->chave)
    {
        no->direita = inserir(no->direita, chave);
        no->direita->pai = no;
    }

    return no;
}



int main()  
{
    struct arvore *minha_arvore = (struct arvore *)malloc(sizeof(struct arvore));
    minha_arvore->raiz = NULL;

    // Inserindo elementos na árvore
    minha_arvore->raiz = inserir(minha_arvore->raiz, 10);
    minha_arvore->raiz = inserir(minha_arvore->raiz, 5);
    minha_arvore->raiz = inserir(minha_arvore->raiz, 15);
    minha_arvore->raiz = inserir(minha_arvore->raiz, 3);
    minha_arvore->raiz = inserir(minha_arvore->raiz, 7);

    // Verificando inserção básica
    printf("Raiz: %d\n", minha_arvore->raiz->chave);
    printf("Filho esquerdo da raiz: %d\n", minha_arvore->raiz->esquerda->chave);
    printf("Filho direito da raiz: %d\n", minha_arvore->raiz->direita->chave);

    printf("Filho esquerdo de %d: %d\n", minha_arvore->raiz->esquerda->chave, minha_arvore->raiz->esquerda->esquerda->chave);
    printf("Filho direito de %d: %d\n", minha_arvore->raiz->esquerda->chave, minha_arvore->raiz->esquerda->direita->chave);

    // Liberar memória se quiser evitar vazamentos
    free(minha_arvore);

    return 0;
}


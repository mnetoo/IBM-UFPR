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

// retorna o menor valor da subarvore
struct nodo* tree_min(struct nodo* no) 
{
    while (no && no->esquerda != NULL)
        no = no->esquerda;

    return no;
}

// retorna o maior valor da subarvore
struct nodo* tree_max(struct nodo* no) 
{
    while (no && no->direita != NULL)
        no = no->direita;
    return no;
}


void em_ordem(struct nodo* no) 
{
    if (no != NULL) 
    {
        em_ordem(no->esquerda);
        printf("%d ", no->chave);
        em_ordem(no->direita);
    }
}


void pre_ordem(struct nodo* no) 
{
    if (no != NULL) 
    {
        printf("%d ", no->chave);
        pre_ordem(no->esquerda);
        pre_ordem(no->direita);
    }
}


void pos_ordem(struct nodo* no) 
{
    if (no != NULL) 
    {
        pos_ordem(no->esquerda);
        pos_ordem(no->direita);
        printf("%d ", no->chave);
    }
}





struct nodo* rotacao_direita(struct nodo* y) 
{
    struct nodo* x = y->esquerda;
    y->esquerda = x->direita;

    if (x->direita != NULL)
        x->direita->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
    {
        // y era a raiz
    }

    else if (y == y->pai->direita)
        y->pai->direita = x;

    else
        y->pai->esquerda = x;


    x->direita = y;
    y->pai = x;

    return x; // nova raiz da subárvore
}



struct nodo* rotacao_esquerda(struct nodo* x) 
{
    struct nodo* y = x->direita;
    x->direita = y->esquerda;

    if (y->esquerda != NULL)
        y->esquerda->pai = x;

    y->pai = x->pai;

    if (x->pai == NULL)
    {
        // x era a raiz
    }

    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;

    else
        x->pai->direita = y;

    y->esquerda = x;
    x->pai = y;

    return y; // nova raiz da subárvore
}





int main() 
{
    struct arvore *minha_arvore = (struct arvore *)malloc(sizeof(struct arvore));
    minha_arvore->raiz = NULL;

    // Inserindo elementos na árvore
    int valores[] = {10, 5, 15, 3, 7, 23, 2, 19, 1, 11};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        minha_arvore->raiz = inserir(minha_arvore->raiz, valores[i]);

    // Impressões básicas
    printf("Raiz: %d\n", minha_arvore->raiz->chave);
    printf("Filho esquerdo da raiz: %d\n", minha_arvore->raiz->esquerda->chave);
    printf("Filho direito da raiz: %d\n", minha_arvore->raiz->direita->chave);

    printf("Mínimo da árvore: %d\n", tree_min(minha_arvore->raiz)->chave);
    printf("Máximo da árvore: %d\n", tree_max(minha_arvore->raiz)->chave);

    printf("\nPercurso em ordem: ");
    em_ordem(minha_arvore->raiz);
    printf("\n");

    printf("Percurso pré-ordem: ");
    pre_ordem(minha_arvore->raiz);
    printf("\n");

    printf("Percurso pós-ordem: ");
    pos_ordem(minha_arvore->raiz);
    printf("\n");

    free(minha_arvore);
    return 0;
}
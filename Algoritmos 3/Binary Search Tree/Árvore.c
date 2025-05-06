#include <stdio.h>
#include <stdlib.h>
#include "Árvore.h"







//================================================================================================

//  Função para criar uma folha na árvore
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

//================================================================================================

// Função para inserir um novo nó na árvore binária
struct nodo* insere(struct nodo *n, int chave)
{
    if (n == NULL)
        return cria_nodo(chave);

    if (chave < n->chave) 
    {
        n->esquerda = insere(n->esquerda, chave);
        n->esquerda->pai = n; // Atualiza o ponteiro do pai
    } 
    else if (chave > n->chave) 
    {
        n->direita = insere(n->direita, chave);
        n->direita->pai = n; // Atualiza o ponteiro do pai
    }

    return n;    
}

//================================================================================================

//  Funçao para encontrar o nó mais a esquerda da sub-árvore a direita (menor valor)
struct nodo* find_min(struct nodo *n)
{
    if(n == NULL)
        return NULL;

    if(n->esquerda)
        return find_min(n->esquerda);

    return n;        
}

//  Funçao para encontrar o nó mais a direita da sub-árvore a esquerda (maior valor)
struct nodo* find_max(struct nodo *n)
{
    if (n == NULL)
        return NULL;

    if (n->direita)
        return find_max(n->direita);

    return n;
}

//================================================================================================

//  Função para encontrar um nó
struct nodo* buscar(struct nodo *no, int chave) 
{
    if (no == NULL)
        return NULL;

    if (no->chave == chave)
        return no;
    
    if (chave < no->chave)
        return buscar(no->esquerda, chave);
    else
        return buscar(no->direita, chave);
}

//================================================================================================

//  Função para rotacionar para a esquerda
struct nodo* rotacionar_esquerda(struct nodo *x)
{
    // 1. y é o filho direito de x
    struct nodo *y = x->direita;

    if (y == NULL)
        return x; // 2. Se x não tem filho direito, não é possível rotacionar

    // 3. O filho esquerdo de y vira o novo filho direito de x
    x->direita = y->esquerda;

    // 4. Se o novo filho direito de x (antes era y->esquerda) não for NULL,
    //    atualiza o ponteiro de pai dele para apontar para x
    if (y->esquerda != NULL)
        y->esquerda->pai = x;

    // 5. Agora y vai subir, então ele precisa herdar o pai de x
    y->pai = x->pai;

    // 6. Aqui ajustamos o ponteiro do pai de x para apontar para y
    //    (se x não for a raiz da árvore)
    if (x->pai != NULL)
    {
        if (x == x->pai->esquerda)
            x->pai->esquerda = y;
        else
            x->pai->direita = y;
    }

    // 7. Agora x vira filho esquerdo de y
    y->esquerda = x;

    // 8. Atualiza o pai de x para ser y (já que y subiu)
    x->pai = y;

    // 9. Retorna o novo topo da subárvore (y)
    return y;
}


// Função para rotacionar para a direita
struct nodo* rotacionar_direita(struct nodo *y) 
{
    // 1. x é o filho esquerdo de y
    struct nodo *x = y->esquerda;

    if (x == NULL)
        return y; // 2. Se y não tem filho esquerdo, não é possível rotacionar

    // 3. O filho direito de x vira o novo filho esquerdo de y
    y->esquerda = x->direita;

    // 4. Se o novo filho esquerdo de y (x->direita) não for NULL,
    //    atualiza o ponteiro de pai dele para apontar para y
    if (x->direita != NULL)
        x->direita->pai = y;

    // 5. Agora x vai subir, então ele precisa herdar o pai de y
    x->pai = y->pai;

    // 6. Ajusta o ponteiro do pai de y para apontar para x
    //    (se y não for a raiz da árvore)
    if (y->pai != NULL) 
    {
        if (y == y->pai->esquerda)
            y->pai->esquerda = x;
        else
            y->pai->direita = x;
    }

    // 7. Agora y vira filho direito de x
    x->direita = y;

    // 8. Atualiza o pai de y para ser x
    y->pai = x;

    // 9. Retorna o novo topo da subárvore (x)
    return x;
}


//================================================================================================

// Função para imprimir a árvore em ordem
void em_ordem(struct nodo *n)
{
    if (n == NULL)
        return;

    em_ordem(n->esquerda);         // Visita a subárvore esquerda
    printf("%d ", n->chave);        // Visita a raiz
    em_ordem(n->direita);          // Visita a subárvore direita
}

// Função para imprimir a árvore em pré ordem
void pre_ordem(struct nodo *n)
{
    if (n == NULL)
        return;

    printf("%d ", n->chave);         // Visita o nó raiz
    pre_ordem(n->esquerda);          // Depois a subárvore esquerda
    pre_ordem(n->direita);           // Depois a subárvore direita
}

// Função para imprimir a árvore em pos ordem
void pos_ordem(struct nodo *n)
{
    if (n == NULL)
        return;

    pos_ordem(n->esquerda);          // Primeiro a subárvore esquerda
    pos_ordem(n->direita);           // Depois a subárvore direita
    printf("%d ", n->chave);         // Por último o nó raiz
}

//================================================================================================
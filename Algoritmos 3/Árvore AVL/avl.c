#include <stdio.h>
#include <stdlib.h>
#include "avl.h"






// Função auxiliar para obter o máximo entre dois números
int max(int a, int b) 
{
    return (a > b) ? a : b;
}



// Retorna a altura de um nó (ou 0 se for NULL)
int altura(No* no) 
{
    return no ? no->altura : 0;
}



// Calcula o fator de balanceamento de um nó
int fator_balanceamento(No* no) 
{
    return no ? altura(no->esq) - altura(no->dir) : 0;
}



// Cria um novo nó com a chave fornecida
No* criar_no(int chave) 
{
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esq = no->dir = NULL;
    no->altura = 1; // Novo nó começa com altura 1
    return no;
}



// Rotação simples à direita
No* rotacao_direita(No* y) 
{
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}



// Rotação simples à esquerda
No* rotacao_esquerda(No* x) 
{
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}



// Inserção balanceada em uma árvore AVL
No* inserir(No* no, int chave) 
{
    // Inserção normal de BST
    if (!no)
        return criar_no(chave);

    if (chave < no->chave)
        no->esq = inserir(no->esq, chave);
    else if (chave > no->chave)
        no->dir = inserir(no->dir, chave);
    else
        return no; // Ignora duplicatas

    // Atualiza altura
    no->altura = 1 + max(altura(no->esq), altura(no->dir));

    // Verifica e corrige balanceamento
    int fb = fator_balanceamento(no);

    // Casos de rotação
    if (fb > 1 && chave < no->esq->chave)
        return rotacao_direita(no); // Caso Esquerda-Esquerda

    if (fb < -1 && chave > no->dir->chave)
        return rotacao_esquerda(no); // Caso Direita-Direita

    if (fb > 1 && chave > no->esq->chave) 
    {
        no->esq = rotacao_esquerda(no->esq); // Caso Esquerda-Direita
        return rotacao_direita(no);
    }

    if (fb < -1 && chave < no->dir->chave) 
    {
        no->dir = rotacao_direita(no->dir); // Caso Direita-Esquerda
        return rotacao_esquerda(no);
    }

    return no;
}



// Retorna o menor nó da subárvore
No* minimo_no(No* no) 
{
    No* atual = no;
    while (atual->esq)
        atual = atual->esq;
    return atual;
}



// Remove um nó da AVL e reequilibra
No* remover(No* raiz, int chave) 
{
    if (!raiz)
        return raiz;

    if (chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);

    else if (chave > raiz->chave)
        raiz->dir = remover(raiz->dir, chave);

    else 
    {
        // Nó com 0 ou 1 filho
        if (!raiz->esq || !raiz->dir) 
        {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (!temp) 
            {
                temp = raiz;
                raiz = NULL;
            } 
            else
                *raiz = *temp;
            free(temp);
        } 
        else 
        {
            // Nó com dois filhos
            No* temp = minimo_no(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = remover(raiz->dir, temp->chave);
        }
    }

    if (!raiz)
        return raiz;

    // Atualiza altura
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // Balanceamento
    int fb = fator_balanceamento(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        return rotacao_direita(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) < 0)
     {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rotacao_esquerda(raiz);

    if (fb < -1 && fator_balanceamento(raiz->dir) > 0)
    {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}



// Impressão em ordem (esquerda, raiz, direita)
void em_ordem(No* raiz) 
{
    if (raiz) 
    {
        em_ordem(raiz->esq);
        printf("%d ", raiz->chave);
        em_ordem(raiz->dir);
    }
}



// Libera toda a árvore
void liberar_arvore(No* raiz) 
{
    if (raiz) 
    {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz);
    }
}
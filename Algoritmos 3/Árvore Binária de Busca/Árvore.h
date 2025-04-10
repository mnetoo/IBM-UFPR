#ifndef ARVORE
#define ARVORE

#include <stdio.h>
#include <stdlib.h>






struct nodo 
{
    int chave;
    struct nodo *esquerda;
    struct nodo *direita;
    struct nodo *pai;
};



//  Função para criar uma folha na árvore
struct nodo* cria_nodo(int chave);

// Função para inserir um novo nó na árvore binária
struct nodo* insere(struct nodo *n, int chave);

//  Funçao para encontrar o nó mais a esquerda da sub-árvore a direita (menor valor)
struct nodo* find_min(struct nodo *n);

//  Funçao para encontrar o nó mais a direita da sub-árvore a esquerda (maior valor)
struct nodo* find_max(struct nodo *n);

//  Função para encontrar um nó
struct nodo* buscar(struct nodo *no, int chave) ;

//  Função para rotacionar para a esquerda
struct nodo* rotacionar_esquerda(struct nodo *x);

//  Função para rotacionar para a direita
struct nodo* rotacionar_direita(struct nodo *y);

// Função para imprimir a árvore em ordem
void em_ordem(struct nodo *n);

// Função para imprimir a árvore em pré ordem
void pre_ordem(struct nodo *n);

// Função para imprimir a árvore em pos ordem
void pos_ordem(struct nodo *n);




#endif
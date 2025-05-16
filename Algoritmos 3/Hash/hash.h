#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 11

// Estrutura do nó da lista (usada para tratar colisões)
struct nodo 
{
    int chave;
    struct nodo* prox;
};


// Função hash simples
int hash(int chave);

// Inserção na tabela
void inserir_h1(struct nodo* tabela[], int chave);

// Inserção na tabela
void inserir_h2(struct nodo* tabela[], int chave);

// Imprimir tabela hash
void imprimirTabela(struct nodo* tabela[]);

// Liberar memória
void liberarTabela(struct nodo* tabela[]);

#endif
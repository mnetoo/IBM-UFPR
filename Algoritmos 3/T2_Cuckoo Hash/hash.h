#ifndef HASH_H
#define HASH_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define M 11
#define VAZIO -1
#define REMOVIDO -2



// Estrutura que representa uma Tabela Hash
struct HashTable
{
    int Tabela1[M];
    int Tabela2[M]; 
};



//=====================================================================================

// Inicializa a tabela hash
void inicializa_hash(struct HashTable *h);

//=====================================================================================

// Função hash 1
int h1(int k);

//=====================================================================================

// Função hash 2
int h2(int k);

//=====================================================================================

// Busca a chave k na tabela (retorna 1 se encontrar, 0 se não encontrar)
int busca(struct HashTable *h, int k);

//=====================================================================================

// Insere a chave k na estrutura, tratando colisões
void inserir(struct HashTable *h, int k);

//=====================================================================================

// Remove a chave k da estrutura (marca como REMOVIDO)
void remover(struct HashTable *h, int k);

//=====================================================================================

// Imprime as duas tabelas (Tabela1 e Tabela2) na tela
void imprime(struct HashTable *h);

//=====================================================================================

void imprimeHash(struct HashTable *h);

//=====================================================================================

#endif
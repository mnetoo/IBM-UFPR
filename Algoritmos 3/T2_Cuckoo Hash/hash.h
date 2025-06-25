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

// Busca a chave k nas tabelas Tabela1 e Tabela2
// Retorna a posição em Tabela1 ou Tabela2 onde a chave está
// Se não encontrar retorna -1
int busca(struct HashTable *h, int k);

//=====================================================================================

// Insere a chave k na tabela, tratando colisões
// Retorna:
//   posição de T1 se inserido lá,
//   posição de T2 se houve colisão e foi movido,
//  -1 se a chave já existia (ignora duplicadas)
int inserir(struct HashTable *h, int k);

//=====================================================================================

// Remove a chave k (marca como REMOVIDO se for encontrada)
// Retorna:
//   1 se a chave foi removida com sucesso
//   0 se a chave não foi encontrada
int remover(struct HashTable *h, int k);

//=====================================================================================

//  Função para imprimir saída formatada
void imprimeHash(struct HashTable *h);

//=====================================================================================

#endif
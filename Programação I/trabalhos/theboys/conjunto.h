// Tipo abstrato de dado "conjunto de inteiros"
// Prof. Carlos Maziero - DINF/UFPR, Out 2024
//
// Este TAD implementa um conjunto de números inteiros com capacidade para
// até CAP valores entre 0 e CAP-1, definida no momento de sua criação.
//
// Implementação com vetor de booleanos.

#ifndef CONJUNTO
#define CONJUNTO

#include <stdbool.h>

// estrutura que implementa um conjunto de inteiros
struct cjto_t
{
  int cap ;			// Capacidade do conjunto
  int num ;			// Número de itens (cardinalidade)
  bool *flag ;			// Vetor de booleanos
} ;

// Cria um conjunto vazio para armazenar até CAP valores entre 0 e CAP-1
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_cria (int cap) ;

// Destrói o conjunto, liberando a memória ocupada por ele.
// Retorno: NULL
struct cjto_t *cjto_destroi (struct cjto_t *c) ;

// Cria e retorna uma cópia do conjunto c.
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_copia (struct cjto_t *c) ;

// Cria um conjunto para até CAP valores preenchido
// com N itens aleatórios na faixa [0...CAP-1].
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_aleat (int n, int cap) ;

// Insere um item no conjunto. Ignora se item não estiver entre 0 e CAP-1.
// Retorno: número de itens no conjunto após a operação ou -1 em erro.
int cjto_insere (struct cjto_t *c, int item) ;

// Retira um item do conjunto. Ignora se item não estiver entre 0 e CAP-1.
// Retorno: número de itens no conjunto após a operação ou -1 em erro.
int cjto_retira (struct cjto_t *c, int item) ;

// Informa a cardinalidade (número de itens) do conjunto.
// Retorno: número de itens no conjunto ou -1 em erro.
int cjto_card (struct cjto_t *c) ;

// Testa se o item está no conjunto.
// Retorno: 1 se está no conjunto, 0 se não está ou -1 em erro.
int cjto_pertence (struct cjto_t *c, int item) ;

// Testa se os conjuntos c1 e c2 têm os mesmos itens.
// Retorno: 1 se c1 == c2, 0 se não ou -1 em erro.
int cjto_iguais (struct cjto_t *c1, struct cjto_t *c2) ;

// Testa se o conjunto c1 contém o conjunto c2.
// Retorno: 1 se c1 contém c2, 0 se não ou -1 em erro.
int cjto_contem (struct cjto_t *c1, struct cjto_t *c2) ;

// Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_uniao (struct cjto_t *c1, struct cjto_t *c2) ;

// Cria e retorna o conjunto interseção entre os conjunto c1 e c2.
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_inter (struct cjto_t *c1, struct cjto_t *c2) ;

// Cria e retorna o conjunto diferença c1 - c2.
// Retorno: ponteiro para o novo conjunto ou NULL em erro.
struct cjto_t *cjto_dif (struct cjto_t *c1, struct cjto_t *c2) ;

// Imprime o conteúdo do conjunto no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois e sem \n no fim
void cjto_imprime (struct cjto_t *c) ;

#endif

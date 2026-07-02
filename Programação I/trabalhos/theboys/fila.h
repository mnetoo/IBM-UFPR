// Tipo abstrato de dado "fila de inteiros"
// Prof. Carlos Maziero - DINF/UFPR, Out 2024
//
// Este TAD implementa uma fila de números inteiros com capacidade
// para até CAP elementos, definida no momento de sua criação.
//
// Implementação com _______________ (completar).

#ifndef FILA
#define FILA

struct nodo_t 
{
  int valor;
  struct nodo_t *prox;
};

struct fila_t
{
  struct nodo_t *primeiro;
  struct nodo_t *ultimo;
  int num; //número elementos
  int capacidade;
  int count;
};

// Cria uma fila vazia e a retorna;
// Retorna NULL em caso de erro
struct fila_t *fila_cria ();

// Remove todos os elementos da fila, libera memória e retorna NULL
struct fila_t *fila_destroi (struct fila_t *f);

// Insere o elemento no final da fila (politica FIFO);
// Retorna o número de elementos na fila após a operação
// ou -1 em caso de erro
int fila_insere (struct fila_t *f, int elem);

// Retira o elemento do inicio da fila (politica FIFO) e o devolve;
// Retorna o número de elementos na fila após a operação
// ou -1 em caso de erro
int fila_retira (struct fila_t *f, int *elem);

// Devolve o primeiro da fila, sem removê-lo
// Retorna o número de elementos na fila ou -1 em caso de erro
int fila_primeiro (struct fila_t *f, int *elem);

// Retorna o tamanho da fila (número de elementos presentes)
int fila_tamanho (struct fila_t *f);

// Retorna a capacidade da fila (número máximo de elementos)
int fila_capacidade (struct fila_t *f);

// Imprime o conteúdo da fila do início ao fim, no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois e sem \n no fim
void fila_imprime (struct fila_t *f);

#endif
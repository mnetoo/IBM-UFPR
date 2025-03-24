#ifndef FILA
#define FILA


#include <stdio.h>
#include <stdlib.h>



typedef struct nodo
{
    int valor;
    struct nodo *proximo;
} nodo ;

typedef struct fila
{
    int tamanho;
    struct nodo* inicio;
    struct nodo* fim;
} fila;





fila* criar_fila();

void inserir_fila(fila* fila, int valor);

void remover_fila(fila* fila);

void destruir_fila(fila* fila);

void imprimir_fila(fila *fila);






#endif
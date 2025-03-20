#ifndef LISTA_CIRCULAR
#define LISTA_CIRCLAR


#include <stdio.h>
#include <stdlib.h>



//  Structs
typedef struct nodo
{
    int valor;
    struct nodo *prox;
} nodo;

typedef struct lista
{
    struct nodo *primeiro;
    struct nodo *ultimo;
    int num;
} lista;



lista* criar_lista();

void inserir_lista(lista* lista, int valor);

int remover_lista(lista* lista);

void destruir_lista(lista* lista);

void imprimir_lista(lista* lista);



















#endif
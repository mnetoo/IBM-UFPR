#ifndef __JUKEFILA__
#define __JUKEFILA__

#include "pedido.h"

typedef struct jukefila{
	pedido *inicio;
	pedido *final;
} jukefila;

jukefila* criar_jukefila();
void inserir_jukefila(pedido* elemento, jukefila* fila);
pedido* consumir_jukefila(jukefila* fila);
unsigned int contar_jukefila(jukefila* fila);
void destruir_jukefila(jukefila *fila);

#endif
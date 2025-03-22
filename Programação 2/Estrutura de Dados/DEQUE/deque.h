#ifndef DEQUE
#define DEQUE

#include <stdio.h>
#include <stdlib.h>


typedef struct nodo
{
    int valor;
    struct nodo* proximo;
} nodo;

typedef struct deque
{
    int capacidade;
    int tamanho;
    struct nodo* primeiro;
    struct nodo* ultimo;
} deque;



deque* criar_deque(int capacidade);

void insere_inicio(deque* deque, int valor);

void insere_fim(deque* deque, int valor);

void retira_inicio(deque* deque);

void retira_fim(deque* deque);

int deque_inicio(deque* deque);

int deque_fim(deque* deque);

int deque_tamanho(deque* deque);

void imprimir_deque(deque* deque);

void destruir_deque(deque* deque);




#endif
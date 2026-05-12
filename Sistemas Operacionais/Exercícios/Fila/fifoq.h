#ifndef FIFOQ_H
#define FIFOQ_H

#include <semaphore.h>
#include <pthread.h>

// Nó da lista encadeada para os semáforos privados
typedef struct Node 
{
    sem_t sem_privado;
    struct Node *next;
} Node;

// Estrutura principal da Fila FIFO
typedef struct fifoQ_s 
{
    pthread_mutex_t mutex_interno;
    Node *head;
    Node *tail;
    int recurso_ocupado;
} FifoQT;

// Protótipos das funções
void init_fifoQ(FifoQT *F);
void espera(FifoQT *F);
void liberaPrimeiro(FifoQT *F);

#endif
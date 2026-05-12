#include "fifoq.h"
#include <stdlib.h>

void init_fifoQ(FifoQT *F) 
{
    pthread_mutex_init(&F->mutex_interno, NULL);
    F->head = NULL;
    F->tail = NULL;
    F->recurso_ocupado = 0;
}

void espera(FifoQT *F) 
{
    pthread_mutex_lock(&F->mutex_interno);

    // Caminho rápido: se livre e sem fila, entra direto
    if (F->recurso_ocupado == 0 && F->head == NULL) 
    {
        F->recurso_ocupado = 1;
        pthread_mutex_unlock(&F->mutex_interno);
        return;
    }

    // Caso contrário, cria um nó e dorme na fila
    Node *novo_no = (Node *)malloc(sizeof(Node));
    sem_init(&novo_no->sem_privado, 0, 0);
    novo_no->next = NULL;

    if (F->tail == NULL)
        F->head = F->tail = novo_no;
    else
    {
        F->tail->next = novo_no;
        F->tail = novo_no;
    }

    pthread_mutex_unlock(&F->mutex_interno);
    
    // Bloqueio efetivo
    sem_wait(&novo_no->sem_privado);

    // Limpeza após ser acordado
    sem_destroy(&novo_no->sem_privado);
    free(novo_no);
}

void liberaPrimeiro(FifoQT *F) 
{
    pthread_mutex_lock(&F->mutex_interno);

    if (F->head != NULL) 
    {
        Node *temp = F->head;
        F->head = F->head->next;
        if (F->head == NULL) F->tail = NULL;

        sem_post(&temp->sem_privado);
    } 
    else
        F->recurso_ocupado = 0;

    pthread_mutex_unlock(&F->mutex_interno);
}
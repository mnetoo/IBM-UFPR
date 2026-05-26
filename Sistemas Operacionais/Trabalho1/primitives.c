/*
Sincronização de Processos via Primitivas: Barreira e Fila FIFO (First-In, First-Out)
Aluno: Marcus Sebastião Adriano Rocha Neto – GRR20240710
Disciplina: CI1215 - Sistemas Operacionais
Professor: Prof. Dr. Wagner M. Nunan Zola
*/

#include "shared.h"
#include <stdio.h>
#include <stdlib.h>


// Implementação da primitiva BARREIRA

void init_barr(barrier_t *barr, int n) 
{
    barr->n = n;
    barr->count = 0;
    sem_init(&barr->mutex, 1, 1);     // Compartilhado entre processos
    sem_init(&barr->turnstile, 1, 0); // Compartilhado entre processos
}

void process_barrier(barrier_t *barr) 
{
    // Trava mutex e incrementa contador de chegada
    sem_wait(&barr->mutex);
    barr->count++;
    
    // Último a chegar libera a todos
    if (barr->count == barr->n)
    {
        for (int i = 0; i < (barr->n - 1); i++) 
            sem_post(&barr->turnstile);
        
        // Prepara para reuso
        barr->count = 0; 
        sem_post(&barr->mutex);
    } 
    else 
    {
        sem_post(&barr->mutex);
        sem_wait(&barr->turnstile);
    }
}


// =========================================================================================================


// Implementação da primitiva FILA FIFO

void init_fifoQ(fifoq_t *F, int n_procs) 
{
    // Mutex multiprocesso
    sem_init(&F->mutex_interno, 1, 1);
    F->head = 0;
    F->tail = 0;
    F->recurso_ocupado = 0;

    // Semáforos começam bloqueados
    for (int i = 0; i < n_procs; i++)
        sem_init(&F->sem_privado[i], 1, 0);
}

void inicia_uso(int pid_logico, int recurso, fifoq_t *F) 
{
    // Trava mutex
    sem_wait(&F->mutex_interno);

    // Se não ocupado e fila vazia o processo avança
    if (F->recurso_ocupado == 0 && F->head == F->tail) 
    {
        F->recurso_ocupado = 1;
        sem_post(&F->mutex_interno);
        return; 
    }

    // Se ocupado processo entra na fila 
    F->fila[F->tail] = pid_logico;
    F->tail = (F->tail + 1) % MAX_PROCS;
    
    sem_post(&F->mutex_interno);
    
    // Bloqueia seu próprio semáforo privado
    sem_wait(&F->sem_privado[pid_logico]);
}

void termina_uso(int recurso, fifoq_t *F) 
{
    // Trava mutex
    sem_wait(&F->mutex_interno);

    // Se tem processo na fila
    if (F->head != F->tail) 
    {
        int prox_processo = F->fila[F->head];
        F->head = (F->head + 1) % MAX_PROCS;
        sem_post(&F->sem_privado[prox_processo]); // Acorda o próximo
    } 
    else
        // Sem nao tem ninguém esperando libera o recurso
        F->recurso_ocupado = 0;

    sem_post(&F->mutex_interno);
}
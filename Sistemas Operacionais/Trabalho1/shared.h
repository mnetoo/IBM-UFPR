/*
Sincronização de Processos via Primitivas: Barreira e Fila FIFO (First-In, First-Out)
Aluno: Marcus Sebastião Adriano Rocha Neto – GRR20240710
Disciplina: CI1215 - Sistemas Operacionais
Professor: Prof. Dr. Wagner M. Nunan Zola
*/

#ifndef SHARED_H
#define SHARED_H

#include <semaphore.h>
#define MAX_PROCS 10

// Estrutura da Barreira
typedef struct 
{
    sem_t mutex;
    sem_t turnstile;
    int count;
    int n;
} barrier_t;

// Estrutura da Fila FIFO
typedef struct 
{
    sem_t mutex_interno;
    sem_t sem_privado[MAX_PROCS]; // Um semáforo para cada processo possível
    int fila[MAX_PROCS];          // Guarda o ID lógico do processo
    int head;
    int tail;
    int recurso_ocupado;
} fifoq_t;

// Memória Compartilhada Geral
typedef struct 
{
    barrier_t barreira;
    fifoq_t fila;
} shared_data_t;

// Protótipos
void init_barr(barrier_t *barr, int n);
void process_barrier(barrier_t *barr);
void init_fifoQ(fifoq_t *F, int n_procs);
void inicia_uso(int pid_logico, int recurso, fifoq_t *F);
void termina_uso(int recurso, fifoq_t *F);

#endif
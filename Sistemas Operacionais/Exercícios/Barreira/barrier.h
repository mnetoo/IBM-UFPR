#ifndef BARRIER_H
#define BARRIER_H

#include <semaphore.h>

typedef struct barrier_s {
    sem_t mutex;      // Protege o acesso ao contador
    sem_t turnstile;  // Onde os processos bloqueiam
    int count;        // Quantos processos já chegaram
    int n;            // Quantos processos são necessários para liberar
} barrier_t;

void init_barr(barrier_t *barr, int n);
void process_barrier(barrier_t *barr);

#endif
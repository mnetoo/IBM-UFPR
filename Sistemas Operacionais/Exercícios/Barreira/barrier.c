#include "barrier.h"
#include <stdio.h>

void init_barr(barrier_t *barr, int n) 
{
    barr->n = n;
    barr->count = 0;
    
    // Segundo argumento '1' significa compartilhado entre PROCESSOS
    sem_init(&barr->mutex, 1, 1);     // Mutex começa aberto (1)
    sem_init(&barr->turnstile, 1, 0); // Turnstile começa fechado (0)
}

void process_barrier(barrier_t *barr) 
{
    // 1. Chegada: incrementa o contador de forma protegida
    sem_wait(&barr->mutex);
    barr->count++;
    
    if (barr->count == barr->n) 
    {
        // 2. Eu sou o último! 
        printf("\n[Barreira] O n-ésimo processo chegou! Liberando todos...\n");
        
        // Libera os n-1 que estão esperando
        for (int i = 0; i < (barr->n - 1); i++) 
            sem_post(&barr->turnstile);
        
        // Reseta para possível reuso (opcional neste exercício)
        barr->count = 0; 
        sem_post(&barr->mutex);
    } 
    else 
    {
        // 3. Ainda faltam processos. Libero o mutex e durmo no turnstile.
        sem_post(&barr->mutex);
        sem_wait(&barr->turnstile);
    }
}
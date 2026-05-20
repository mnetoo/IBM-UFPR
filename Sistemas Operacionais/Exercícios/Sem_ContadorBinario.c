#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// 1. Definição da Estrutura do Semáforo Contador
typedef struct {
    int contador;    // O valor do semáforo contador
    sem_t mutex;     // Semáforo binário para proteger o "contador"
    sem_t delay;     // Semáforo binário para bloquear/adiar os processos
} SemaforoContador;

// 2. Inicialização do Semáforo Contador
void sem_contador_init(SemaforoContador *s, int valor_inicial) {
    s->contador = valor_inicial;
    
    // mutex inicializa em 1 (LIVRE) para permitir o primeiro acesso à estrutura
    sem_init(&(s->mutex), 0, 1); 
    
    // delay inicializa em 0 (TRANCADO). Quem bater aqui vai dormir imediatamente
    sem_init(&(s->delay), 0, 0); 
}

// 3. Operação WAIT (P)
void sem_contador_wait(SemaforoContador *s) {
    sem_wait(&(s->mutex)); // Tranca acesso à variável interna 'contador'
    
    s->contador--; // Consome um recurso
    
    if (s->contador < 0) {
        // Se não há recursos disponíveis, o processo tem de bloquear.
        // Mas antes de dormir, ele DEVE libertar o mutex, senão mais ninguém entra!
        sem_post(&(s->mutex)); 
        
        // Dorme no semáforo binário de atraso (que está inicializado em 0)
        sem_wait(&(s->delay)); 
    } else {
        // Se havia recurso disponível, apenas liberta o mutex e prossegue
        sem_post(&(s->mutex)); 
    }
}

// 4. Operação SIGNAL (V / POST)
void sem_contador_signal(SemaforoContador *s) {
    sem_wait(&(s->mutex)); // Tranca acesso à variável interna 'contador'
    
    s->contador++; // Devolve um recurso
    
    if (s->contador <= 0) {
        // Se o contador continua menor ou igual a zero após o incremento,
        // significa que existe pelo menos um processo bloqueado no 'delay'.
        // Acorda UM processo que estava a dormir
        sem_post(&(s->delay)); 
    }
    
    sem_post(&(s->mutex)); // Liberta o mutex interno
}

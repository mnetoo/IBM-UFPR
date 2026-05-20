#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define MAX 100 // Capacidade máxima da pilha

// 1. Definição da Estrutura da Pilha Concorrente
typedef struct {
    int dados[MAX];
    int topo;
    sem_t mutex; // Semáforo para garantir Exclusão Mútua
} PilhaConcorrente;

// 2. Inicialização da Pilha
void inicializar_pilha(PilhaConcorrente *p) {
    p->topo = -1; // Pilha começa vazia
    
    // Inicializa o semáforo 'mutex' com valor 1 (Livre)
    // Parâmetros: (endereço, 0 = compartilhado entre threads, valor inicial)
    sem_init(&(p->mutex), 0, 1); 
}

// 3. Operação PUSH (Inserir)
bool push(PilhaConcorrente *p, int valor) {
    sem_wait(&(p->mutex)); // ENTRADA NA RC: Tranca o acesso à pilha

    // --- REGIÃO CRÍTICA ---
    if (p->topo >= MAX - 1) {
        printf("[ERRO] Pilha cheia! Overflow.\n");
        sem_post(&(p->mutex)); // ATENÇÃO: Destranca antes de sair!
        return false;
    }

    p->topo++;
    p->dados[p->topo] = valor;
    // ----------------------

    sem_post(&(p->mutex)); // SAÍDA NA RC: Destranca o acesso
    return true;
}

// 4. Operação POP (Remover)
bool pop(PilhaConcorrente *p, int *resultado) {
    sem_wait(&(p->mutex)); // ENTRADA NA RC: Tranca o acesso à pilha

    // --- REGIÃO CRÍTICA ---
    if (p->topo == -1) {
        printf("[ERRO] Pilha vazia! Underflow.\n");
        sem_post(&(p->mutex)); // ATENÇÃO: Destranca antes de sair!
        return false;
    }

    *resultado = p->dados[p->topo];
    p->topo--;
    // ----------------------

    sem_post(&(p->mutex)); // SAÍDA NA RC: Destranca o acesso
    return true;
}

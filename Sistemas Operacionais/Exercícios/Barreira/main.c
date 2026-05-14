#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/mman.h> // Para mmap (Shared Memory simplificada)
#include "barrier.h"

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Uso: %s <numero_de_processos>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int nProc = 0; // 0 para o Pai

    /* 
       INDICANDO SHARED MEMORY:
       Em um trabalho real, você usaria shmget/shmat ou mmap.
       Aqui usaremos mmap para criar uma área visível a pai e filhos.
    */
    barrier_t *barr = mmap(NULL, sizeof(barrier_t), 
                          PROT_READ | PROT_WRITE, 
                          MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    init_barr(barr, n);

    printf("Pai (nProc=0) PID: %d. Criando %d filhos...\n", getpid(), n-1);

    for (int i = 1; i < n; i++) 
    {
        pid_t pid = fork();
        if (pid == 0) 
        {
            nProc = i; // Identificação lógica do filho
            break;     // Filho sai do loop de criação
        }
    }

    // --- CÓDIGO EXECUTADO POR TODOS OS N PROCESSOS ---
    
    printf("Processo nProc: %d | PID: %d | Pai PID: %d\n", nProc, getpid(), getppid());

    // Inicializa semente aleatória diferente para cada processo
    srand(time(NULL) ^ (getpid() << 16));
    int ns = rand() % n;

    printf("Processo %d vai dormir por %d segundos...\n", nProc, ns);
    sleep(ns);
    printf("Processo %d acordou e chegou na barreira.\n", nProc);

    process_barrier(barr);

    printf(">>> Processo %d SAIU da barreira!\n", nProc);

    // --- FINALIZAÇÃO ---
    
    if (nProc != 0)
        exit(0); // Filhos terminam
    else 
    {
        // Pai espera todos os filhos para limpar a casa
        for (int i = 1; i < n; i++) 
            wait(NULL);
            
        sem_destroy(&barr->mutex);
        sem_destroy(&barr->turnstile);
        munmap(barr, sizeof(barrier_t));
        printf("Pai finalizou tudo.\n");
    }

    return 0;
}
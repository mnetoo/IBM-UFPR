/*
Sincronização de Processos via Primitivas: Barreira e Fila FIFO (First-In, First-Out)
Aluno: Marcus Sebastião Adriano Rocha Neto – GRR20240710
Disciplina: CI1215 - Sistemas Operacionais
Professor: Prof. Dr. Wagner M. Nunan Zola
*/

#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#define NUM_PROCS 3

int main() 
{
    // Pai cria estruturas compartilhadas via mmap 
    shared_data_t *shm = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shm == MAP_FAILED) 
    {
        perror("Erro no mmap");
        exit(1);
    }

    // Inicializa fila e barreira
    init_barr(&shm->barreira, NUM_PROCS);
    init_fifoQ(&shm->fila, NUM_PROCS);

    srand(time(NULL));
    int recurso = rand() % 100;
    
    // Vetor local para mapeamento, guarda o PID real indexado pelo número lógico
    pid_t tabela_pids[NUM_PROCS];

    // Criando filhos
    for (int i = 0; i < NUM_PROCS; i++) 
    {
        pid_t pid = fork();
        
        if (pid < 0) 
        {
            perror("Erro ao executar fork");
            exit(1);
        }
        else if (pid > 0) 
            tabela_pids[i] = pid;
        else 
        { 
            // Código do Processo Filho
            int pi = i; // Número lógico
            srand(time(NULL) ^ getpid()); // Semente única por processo

            printf("--Processo: %d chegando na barreira\n", pi);
            process_barrier(&shm->barreira);
            printf("**Processo: %d saindo da barreira\n", pi);

            // Loop de uso exclusivo FIFO de recursos
            for (int uso = 0; uso < 3; uso++) 
            {
                // PRÓLOGO
                int s = rand() % 4;
                printf("Processo: %d Prologo: %d de %d segundos\n", pi, uso, s);
                sleep(s);
                inicia_uso(pi, recurso, &shm->fila);

                // USO
                s = rand() % 4;
                printf("Processo: %d USO: %d por %d segundos\n", pi, uso, s); 
                sleep(s);
                termina_uso(recurso, &shm->fila);

                // EPÍLOGO
                s = rand() % 4;
                printf("Processo: %d Epilogo: %d de %d segundos\n", pi, uso, s);
                sleep(s);
            }

            printf("--Processo: %d chegando novamente na barreira\n", pi); 
            process_barrier(&shm->barreira);
            printf("++Processo: %d saindo da barreira novamente\n", pi);

            exit(0); // Filho termina
        }
    }

    // O main espera todos os filhos terminarem 
    for (int i = 0; i < NUM_PROCS; i++) 
    {
        int status;
        pid_t child_pid = wait(&status);
        
        // Busca linear na tabela local para traduzir o PID real em número lógico
        int numero_logico = -1;
        for (int j = 0; j < NUM_PROCS; j++) 
        {
            if (tabela_pids[j] == child_pid) 
            {
                numero_logico = j;
                break;
            }
        }
        
        // Impressão dos número lógicos e PID dos filhos que terminaram
        printf("+++ Filho de número lógico %d e pid %d terminou!\n", numero_logico, child_pid);    
    }

    // Limpeza
    munmap(shm, sizeof(shared_data_t));
    return 0;
}
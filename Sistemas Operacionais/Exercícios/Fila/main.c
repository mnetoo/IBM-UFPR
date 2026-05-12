#include <stdio.h>
#include <unistd.h>
#include "fifoq.h"

FifoQT fila;

void* cliente(void* arg) 
{
    long id = (long)arg;

    printf("[Thread %ld] Chegou e vai chamar espera().\n", id);
    espera(&fila);

    // SEÇÃO CRÍTICA
    printf("  => [Thread %ld] ENTROU no recurso. (Trabalhando...)\n", id);
    sleep(1); 
    printf("  <= [Thread %ld] SAIU do recurso.\n", id);
    // FIM DA SEÇÃO CRÍTICA

    liberaPrimeiro(&fila);
    return NULL;
}

int main() 
{
    pthread_t threads[5];
    init_fifoQ(&fila);

    for (long i = 0; i < 5; i++) 
    {
        pthread_create(&threads[i], NULL, cliente, (void*)i);
        usleep(100000); // Pequeno delay para garantir ordem de criação no print
    }

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    printf("Teste finalizado. Se as saídas foram ordenadas, parabéns.\n");
    return 0;
}
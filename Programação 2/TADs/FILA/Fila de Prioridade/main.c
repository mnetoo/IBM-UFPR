#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"



int main()
{
    // Criar uma fila de prioridade
    fila *minhaFila = criar_fprio();
    
    int *item1 = (int*)malloc(sizeof(int));
    int *item2 = (int*)malloc(sizeof(int));
    int *item3 = (int*)malloc(sizeof(int));
    
    *item1 = 10;
    *item2 = 20;
    *item3 = 30;
    
    inserir_fprio(minhaFila, item1, sizeof(int), 3);
    inserir_fprio(minhaFila, item2, sizeof(int), 2);
    inserir_fprio(minhaFila, item3, sizeof(int), 1);
    
    
    // Imprimir o conteúdo da fila
    printf("Fila após inserções:\n");
    imprimir_fprio(minhaFila);
    printf("\n");

    // Retirar o primeiro item da fila
    int tipo, prio;
    int *itemRetirado = (int*)retirar_fprio(minhaFila, &tipo, &prio);
    if (itemRetirado)
    {
        printf("Item retirado: %d, Tipo: %d, Prioridade: %d\n", *itemRetirado, tipo, prio);
    }


    // Imprimir o conteúdo da fila após a retirada
    printf("\nFila após retirada:\n");
    imprimir_fprio(minhaFila);
    printf("\n");

    // Verificar o tamanho da fila
    printf("Tamanho da fila: %d\n", fprio_tamanho(minhaFila));

    // Destruir a fila e liberar memória
    destruir_fprio(minhaFila);
    
    return 0;
}
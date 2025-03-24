#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main()
{
    fila *f = criar_fila();
    if (!f)
        return 1;

    printf("Inserindo valores na fila...\n");
    inserir_fila(f, 10);
    inserir_fila(f, 20);
    inserir_fila(f, 30);
    imprimir_fila(f); // Deve imprimir: 10 20 30

    printf("Removendo um elemento...\n");
    remover_fila(f);
    imprimir_fila(f); // Deve imprimir: 20 30

    printf("Destruindo a fila...\n");
    destruir_fila(f);

    return 0;
}
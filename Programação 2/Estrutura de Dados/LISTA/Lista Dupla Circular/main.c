#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"





int main ()
{
    lista *l = criar_lista();

    printf("Inserindo valores na lista: \n\n");
    
    printf("Inserindo 10\n");
    inserir_lista(l, 10);
    imprimir_lista(l);

    printf("Inserindo 20\n");
    inserir_lista(l, 20);
    imprimir_lista(l);

    printf("Inserindo 30\n");
    inserir_lista(l, 30);
    imprimir_lista(l);

    printf("Inserindo 40\n");
    inserir_lista(l, 40);
    imprimir_lista(l);

    printf("Inserindo 50\n");
    inserir_lista(l, 50);
    imprimir_lista(l);


    printf("Removendo valores da lista: \n\n");

    printf("Removendo 10\n");
    remover_lista(l, 10);
    imprimir_lista(l);

    printf("Removendo 20\n");
    remover_lista(l, 20);
    imprimir_lista(l);

    printf("Removendo 30\n");
    remover_lista(l, 30);
    imprimir_lista(l);

    printf("Removendo 40\n");
    remover_lista(l, 40);
    imprimir_lista(l);

    printf("Removendo 50\n");
    remover_lista(l, 50);
    imprimir_lista(l);

    printf("Destruindo a lista\n");
    destruir_lista(l);
    

    return 0;
}
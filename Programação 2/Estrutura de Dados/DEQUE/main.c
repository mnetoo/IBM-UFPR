#include <stdio.h>
#include <stdlib.h>
#include "deque.h"



int main()
{
    int cap;
    deque *d;

    printf("Digite a capacidade do deque: ");
    scanf("%d", &cap);
    printf("\n");

    if(cap > 0)
        d = criar_deque(cap);
    else
    {
        printf("\nCapacidade do deque deve ser maior de zero!\n");
        return 0;
    }

    printf("\nInserindo itens no Deque...\n\n");

    printf("Inserindo 10 no inicio:\n");
    insere_inicio(d, 10);
    imprimir_deque(d);

    printf("Inserindo 20 no inicio:\n");
    insere_inicio(d, 20);
    imprimir_deque(d);

    printf("Inserindo 30 no fim:\n");
    insere_fim(d, 30);
    imprimir_deque(d);

    printf("Inserindo 40 no inicio:\n");
    insere_fim(d, 40);
    imprimir_deque(d);

    printf("Inserindo 50 no inicio:\n");
    insere_inicio(d, 50);
    imprimir_deque(d);





    printf("\nInicio do Deque...\n");
    int inicio = deque_inicio(d);
    printf("Inicio: %d\n", inicio);

    printf("\nFim do Deque...\n");
    int fim = deque_fim(d);
    printf("Fim: %d\n", fim);

    printf("\nTamanho do Deque...\n");
    int tam = deque_tamanho(d);
    printf("Tamanho: %d\n", tam);




    printf("\nRetirando itens do Deque...\n\n");

    printf("Retirando inicio:\n");
    retira_inicio(d);
    imprimir_deque(d);

    printf("Retirando fim:\n");
    retira_fim(d);
    imprimir_deque(d);

    printf("Retirando inicio:\n");
    retira_inicio(d);
    imprimir_deque(d);

    printf("Retirando fim:\n");
    retira_fim(d);
    imprimir_deque(d);

    printf("Retirando inicio:\n");
    retira_inicio(d);
    imprimir_deque(d);



    printf("\nDestruindo Deque...\n");
    destruir_deque(d);

    return 0;
}
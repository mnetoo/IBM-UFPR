#include <stdio.h>
#include <stdlib.h>
#include "234.h"

int main() 
{
    No234 *raiz = NULL;

    int op, valor;

    do {
        printf("\n--- Árvore 2-3-4 ---\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Imprimir árvore\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch(op) 
        {
            case 1:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                inserir(&raiz, valor);
                break;

            case 2:
                printf("\nImpressão da árvore:\n");
                imprimirArvoreVertical(raiz);

                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (op != 0);

    liberarArvore(raiz);
    return 0;
}

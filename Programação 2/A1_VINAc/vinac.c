#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membro.h"
#include "functions.h"


int main(int argc, char *argv[]) 
{
    if (argc < 3) 
    {
        printf("Uso: %s <opção> <arquivo> [membro1 membro2 ...]\n", argv[0]);
        return 1;
    }

    char *opcao = argv[1];
    char *arquivo = argv[2];

    printf("Opção: %s\n", opcao);
    printf("Arquivo: %s\n", arquivo);

    if (strcmp(opcao, "-ip") == 0) 
        return ip_option(arquivo, argc, argv);

    else if (strcmp(opcao, "-ic") == 0)
        return ic_option(arquivo, argc, argv);

    else if (strcmp(opcao, "-c") == 0)
        return c_option(arquivo, argc, argv);

    return 0;
}
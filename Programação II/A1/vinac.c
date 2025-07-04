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

    // Insere sem compressão
    if (strcmp(opcao, "-p") == 0) 
        return p_option(arquivo, argc, argv);

    // Insere com compressão
    else if (strcmp(opcao, "-i") == 0)
        return i_option(arquivo, argc, argv);
    
    // Remove os membros indicados
    else if (strcmp(opcao, "-r") == 0)
        return r_option(arquivo, argc, argv);

    // Extrai os membros indicados
    else if (strcmp(opcao, "-x") == 0)
        return x_option(arquivo, argc, argv);

    // Move os membros indicados
    else if (strcmp(opcao, "-m") == 0)
        return m_option(arquivo, argc, argv);

    // Move os membros indicados
    else if (strcmp(opcao, "-z") == 0)
        return z_option(arquivo, argc, argv);   

    // Lista os membros do archive
    else if (strcmp(opcao, "-c") == 0)
        return c_option(arquivo);

    return 0;
}
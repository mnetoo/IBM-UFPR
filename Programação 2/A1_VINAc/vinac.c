/*
Trabalho desenvolvido para a disciplina de Programação 2 - Turma Vinicius Fulber
Aluno: Marcus Sebastião Adriano Rocha Neto GRR20240710
O Arquivador - VINAc (Compressor e Descompressor de arquivos)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membro.h"
#include "utils.h"




int main(int argc, char *argv[]) 
{
    if (argc < 3) 
    {
        printf("Uso: %s <opção> <archive> [membro1 membro2 ...]\n", argv[0]);
        return 1;
    }

    // Pega a flag/opção
    //  -ip -ic -m -r -x -c
    char *opcao = argv[1];

    // Nome do arquivo "archive.vc"
    char *arquivo = argv[2];

    printf("Opção: %s\n", opcao);
    printf("Arquivo: %s\n", arquivo);

    if (strcmp(opcao, "-ip") == 0) 
    {
        if (argc < 4) {
            printf("Uso: %s -ip <archive> <membro1> [membro2 ...]\n", argv[0]);
            return 1;
        }

        printf("\nInserindo %d membro(s) sem compressão no archive '%s':\n", argc - 3, arquivo);

        for (int i = 3; i < argc; i++) 
        {
            const char *nome_membro = argv[i];

            FILE *teste = fopen(nome_membro, "rb");
            if (!teste) {
                printf("Erro: não foi possível abrir o arquivo '%s'. Pulando...\n", nome_membro);
                continue;
            }
            fclose(teste);

            printf("\nCriando membro com base em: %s\n", nome_membro);

            Membro m = criar_membro(nome_membro, i - 2); // ordem = 1, 2, 3, ...
            imprimir_membro(&m);

            // Futuramente: salvar no arquivo archive (.vc)
        }

        return 0;
    }

    // Lista os membros se houver (apenas para visualização geral)
    if (argc > 3) 
    {
        printf("Membros:\n");
        for (int i = 3; i < argc; i++) 
        {
            printf(" - %s\n", argv[i]);
        }
    } 
    else 
    {
        printf("Nenhum membro especificado.\n");
    }

    return 0;
}
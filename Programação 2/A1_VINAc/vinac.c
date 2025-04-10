/*

Trabalho desenvolvido para a disciplina de Programação 2 - Turma Vinicius Fulber
Aluno: Marcus Sebastião Adriano Rocha Neto GRR20240710
O Arquivador - VINAc (Compressor e Descompressor de arquivos)

*/

#include <stdio.h>
#include <stdlib.h>



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

    // Nome do arquivo "archive.vs"
    char *arquivo = argv[2];

    printf("Opção: %s\n", opcao);
    printf("Arquivo: %s\n", arquivo);

    // Lista os membros se houver
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
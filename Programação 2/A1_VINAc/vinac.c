#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membro.h"
#include "utils.h"

#define MAX_MEMBROS 1024

int main(int argc, char *argv[]) 
{
    if (argc < 3) 
    {
        printf("Uso: %s <opção> <archive> [membro1 membro2 ...]\n", argv[0]);
        return 1;
    }

    char *opcao = argv[1];
    char *arquivo = argv[2];

    printf("Opção: %s\n", opcao);
    printf("Arquivo: %s\n", arquivo);

    if (strcmp(opcao, "-ip") == 0) 
    {
        if (argc < 4) 
        {
            printf("Uso: %s -ip <archive> <membro1> [membro2 ...]\n", argv[0]);
            return 1;
        }

        FILE *archive = fopen(arquivo, "wb");
        if (!archive) 
        {
            printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
            return 1;
        }

        Membro membros[MAX_MEMBROS];
        int qtd_membros = 0;

        for (int i = 3; i < argc; i++) 
        {
            const char *nome_membro = argv[i];
            FILE *f = fopen(nome_membro, "rb");
            if (!f) 
            {
                printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
                continue;
            }

            // Preenche os dados do membro
            Membro m = criar_membro(nome_membro, i - 2);
            m.offset = ftell(archive);  // onde começa o conteúdo

            // Copia o conteúdo do arquivo para o archive
            char buffer[1024];
            size_t lidos;
            while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0) 
            {
                fwrite(buffer, 1, lidos, archive);
            }

            fclose(f);

            membros[qtd_membros++] = m; // salva o membro para depois gravar no diretório
        }

        // Depois de gravar todos os conteúdos, agora gravamos o diretório:
        long inicio_diretorio = ftell(archive);

        printf("\nTotal de membros: %d\n", qtd_membros);
        for (int i = 0; i < qtd_membros; i++) 
        {
            escrever_membro(archive, &membros[i]);
            imprimir_membro(&membros[i]);
        }

        fclose(archive);

        printf("\nArchive criado com sucesso!\n");
        printf("Diretório inicia em: %ld bytes\n", inicio_diretorio);

        return 0;
    }

    return 0;
}
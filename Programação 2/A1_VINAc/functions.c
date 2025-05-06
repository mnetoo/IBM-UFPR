#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membro.h"
#include "lz.h"
#include "functions.h"

#define MAX_MEMBROS 1024




//============================================================================================================================


//  Função que obtém a data de modificação de um arquivo
time_t obter_data_modificacao(const char *nome_arquivo) 
{
    struct stat info;

    if (stat(nome_arquivo, &info) == 0) 
        return info.st_mtime;

    return 0;
}


//============================================================================================================================


//  Função que obtém o UID do usuário atual
int obter_uid() 
{
    return getuid();  // pega UID do usuário atual
}


//============================================================================================================================


//  Função para inserir sem compressão
int ip_option(char *arquivo, int argc, char *argv[]) 
{
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

        Membro m = criar_membro(nome_membro, i - 2);
        m.offset = ftell(archive);

        char buffer[1024];
        size_t lidos;
        while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0) 
        {
            fwrite(buffer, 1, lidos, archive);
        }

        fclose(f);
        membros[qtd_membros++] = m;
    }

    // Agora grava o vetor de membros
    fwrite(membros, sizeof(Membro), qtd_membros, archive);

    // E por fim, grava a quantidade de membros no final (últimos 4 bytes do arquivo)
    fwrite(&qtd_membros, sizeof(int), 1, archive);

    fclose(archive);

    printf("\nArchive criado com sucesso!\n");
    printf("Total de membros: %d\n", qtd_membros);
    for (int i = 0; i < qtd_membros; i++) 
    {
        imprimir_membro(&membros[i]);
    }

    return 0;
}


//============================================================================================================================


//  Função para inserir com compressão
int ic_option(char *arquivo, int argc, char *argv[]) 
{
    FILE *archive = fopen(arquivo, "wb");
    if (!archive) 
    {
        printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // Move ponteiro para o final para inserir novos dados
    fseek(archive, 0, SEEK_END);

    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        // Descobre tamanho do arquivo
        fseek(f, 0, SEEK_END);
        long tamanho_original = ftell(f);
        rewind(f);

        char *conteudo_original = malloc(tamanho_original);
        fread(conteudo_original, 1, tamanho_original, f);
        fclose(f);

        // Aloca o dobro para garantir espaço comprimido
        char *conteudo_comp = malloc(tamanho_original * 2);
        int tamanho_comp = LZ_Compress(
            (unsigned char *)conteudo_original,
            (unsigned char *)conteudo_comp,
            tamanho_original
        );
        free(conteudo_original);

        // Verifica se o membro já existe
        int existe = -1;
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[j].nome, nome_membro) == 0) 
            {
                existe = j;
                break;
            }
        }

        long offset = ftell(archive);
        fwrite(conteudo_comp, 1, tamanho_comp, archive);
        free(conteudo_comp);

        if (existe != -1) 
        {
            // Substitui membro existente
            membros[existe].offset = offset;
            membros[existe].tamanho_comp = tamanho_comp;
            membros[existe].modificado_em = time(NULL); // Atualiza a data de modificação
        } 
        else 
        {
            // Insere novo membro
            Membro m = criar_membro(nome_membro, qtd_membros + 1);
            m.offset = offset;
            m.tamanho_original = tamanho_original;
            m.tamanho_comp = tamanho_comp;
            m.modificado_em = time(NULL); // A data de modificação é a hora atual
            membros[qtd_membros++] = m;
        }
    }

    printf("\nArchive criado com sucesso!\n");
    printf("Total de membros: %d\n", qtd_membros);
    // Grava o novo diretório
    long inicio_diretorio = ftell(archive);
    for (int i = 0; i < qtd_membros; i++) 
    {
        escrever_membro(archive, &membros[i]);
        imprimir_membro(&membros[i]);  // Exibe info do membro
    }

    // Grava a quantidade de membros no final (últimos 4 bytes do arquivo)
    fwrite(&qtd_membros, sizeof(int), 1, archive);

    fclose(archive);

    printf("\nArchive atualizado com sucesso!\n");
    printf("Novo diretório inicia em: %ld bytes\n", inicio_diretorio);

    return 0;
}


//============================================================================================================================


// Função para listar os membros do archive
int c_option(char *arquivo, int argc, char *argv[]) 
{
    // Abre o arquivo para leitura
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir o arquivo de archive '%s'\n", arquivo);
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);  // Lê o diretório de membros

    printf("Conteúdo do archive '%s':\n", arquivo);
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("Ordem  Nome do Arquivo             UID   Tamanho Original   Tamanho Comprimido   Data de Modificação\n");
    printf("-----------------------------------------------------------------------------------------------------\n");

    // Exibe informações dos membros
    for (int i = 0; i < qtd_membros; i++) 
    {
        char data_modificacao[20];
        strftime(data_modificacao, sizeof(data_modificacao), "%Y-%m-%d %H:%M:%S", localtime(&membros[i].modificado_em));

        printf("%-6d %-25s %-5d %-18ld %-19ld %-19s\n",
            membros[i].ordem,
            membros[i].nome,
            membros[i].uid,
            membros[i].tamanho_original,
            membros[i].tamanho_comp,
            data_modificacao);
    }

    fclose(archive);
    return 0;
}


//============================================================================================================================
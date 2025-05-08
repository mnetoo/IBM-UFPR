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


int p_option(char *arquivo, int argc, char *argv[]) 
{
    Membro membros_existentes[MAX_MEMBROS];
    int qtd_existentes = 0;

    // Tenta abrir o archive existente para leitura
    FILE *archive = fopen(arquivo, "rb");
    if (archive) 
    {
        // Vai para o final do arquivo para ler a quantidade de membros
        fseek(archive, -sizeof(int), SEEK_END);
        fread(&qtd_existentes, sizeof(int), 1, archive);

        // Volta para onde começa o vetor de membros
        fseek(archive, -(sizeof(int) + qtd_existentes * sizeof(Membro)), SEEK_END);
        fread(membros_existentes, sizeof(Membro), qtd_existentes, archive);

        fclose(archive); // fecha o archive original
    }

    // Reabre o arquivo para escrita binária (recria)
    archive = fopen(arquivo, "wb");
    if (!archive) 
    {
        printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
        return 1;
    }

    Membro membros_finais[MAX_MEMBROS];
    int qtd_finais = 0;

    // Verifica se algum membro existente deve ser mantido (não substituído)
    for (int i = 0; i < qtd_existentes; i++) 
    {
        int substituir = 0;
        for (int j = 3; j < argc; j++) 
        {
            if (strcmp(membros_existentes[i].nome, argv[j]) == 0) 
            {
                printf("Membro '%s' já existe. Substituindo...\n", argv[j]);
                substituir = 1; // esse será substituído por nova versão
                break;
            }
        }

        if (!substituir) 
        {
            FILE *f = fopen(membros_existentes[i].nome, "rb");
            if (!f) 
            {
                printf("Aviso: não foi possível reabrir '%s'. Pulando...\n", membros_existentes[i].nome);
                continue;
            }

            Membro m = membros_existentes[i];
            m.offset = ftell(archive);
            m.comprimido = 0; // sempre 0 para inserção sem compressão

            char buffer[1024];
            size_t lidos;
            fseek(f, 0, SEEK_SET);
            while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0)
                fwrite(buffer, 1, lidos, archive);

            fclose(f);
            membros_finais[qtd_finais++] = m;
        }
    }

    // Agora adiciona os novos membros (incluindo substituições)
    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        Membro m = criar_membro(nome_membro, qtd_finais + 1);
        m.offset = ftell(archive);
        m.comprimido = 0; // sempre 0 para inserção sem compressão

        char buffer[1024];
        size_t lidos;
        while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0)
            fwrite(buffer, 1, lidos, archive);

        fclose(f);
        membros_finais[qtd_finais++] = m;
    }

    // Corrige as ordens dos membros antes de gravar
    for (int i = 0; i < qtd_finais; i++)
        membros_finais[i].ordem = i + 1;

    // Grava vetor de membros no final do arquivo
    fwrite(membros_finais, sizeof(Membro), qtd_finais, archive);

    // Grava o número de membros (últimos 4 bytes)
    fwrite(&qtd_finais, sizeof(int), 1, archive);

    fclose(archive);

    printf("\nArchive atualizado com sucesso!\n");
    printf("Total de membros: %d\n", qtd_finais);
    for (int i = 0; i < qtd_finais; i++) 
        imprimir_membro(&membros_finais[i]);

    return 0;
}


//============================================================================================================================

// Função para inserir arquivos com compressão
int i_option(char *arquivo, int argc, char *argv[]) 
{
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        archive = fopen(arquivo, "w+b");
        if (!archive) 
        {
            printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
            return 1;
        }
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    fseek(archive, 0, SEEK_END);  // Move ponteiro para o final

    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        fseek(f, 0, SEEK_END);
        long tamanho_original = ftell(f);
        rewind(f);

        char *conteudo_original = malloc(tamanho_original);
        fread(conteudo_original, 1, tamanho_original, f);
        fclose(f);

        char *conteudo_comp = malloc(tamanho_original * 2);
        int tamanho_comp = LZ_Compress(
            (unsigned char *)conteudo_original,
            (unsigned char *)conteudo_comp,
            tamanho_original
        );

        // Verifica se a compressão foi eficiente
        int usar_original = (tamanho_comp >= tamanho_original);
        char *dados_finais = usar_original ? conteudo_original : conteudo_comp;
        int tamanho_final = usar_original ? tamanho_original : tamanho_comp;

        if (usar_original)
            printf("Aviso: compressão de '%s' ineficiente. Armazenando arquivo original.\n", nome_membro);

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
        fwrite(dados_finais, 1, tamanho_final, archive);

        free(conteudo_original);
        free(conteudo_comp);

        if (existe != -1) 
        {
            printf("Membro '%s' já existe. Substituindo...\n", nome_membro);

            membros[existe].offset = offset;
            membros[existe].tamanho_original = tamanho_original;
            membros[existe].tamanho_comp = tamanho_final;
            membros[existe].modificado_em = time(NULL);
            membros[existe].comprimido = !usar_original; // ✅ Define se foi comprimido
        } 
        else 
        {
            Membro m = criar_membro(nome_membro, qtd_membros + 1);
            m.offset = offset;
            m.tamanho_original = tamanho_original;
            m.tamanho_comp = tamanho_final;
            m.modificado_em = time(NULL);
            m.comprimido = !usar_original; // ✅ Define se foi comprimido
            membros[qtd_membros++] = m;
        }
    }

    // Corrige a ordem dos membros
    for (int i = 0; i < qtd_membros; i++) 
        membros[i].ordem = i + 1;

    printf("\nArchive criado com sucesso!\n");
    printf("Total de membros: %d\n", qtd_membros);

    long inicio_diretorio = ftell(archive);
    for (int i = 0; i < qtd_membros; i++) 
    {
        escrever_membro(archive, &membros[i]);
        imprimir_membro(&membros[i]);
    }

    fwrite(&qtd_membros, sizeof(int), 1, archive);
    fclose(archive);

    printf("\nArchive atualizado com sucesso!\n");
    printf("Novo diretório inicia em: %ld bytes\n", inicio_diretorio);

    return 0;
}



//============================================================================================================================


// Função para listar os membros do archive com formatação aprimorada
int c_option(char *arquivo) 
{
    // Abre o arquivo para leitura
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir o arquivo de archive '%s'\n", arquivo);
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // Cabeçalho melhor formatado
    printf("\n╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-107s  ║\n", "                                            CONTEÚDO DO ARCHIVE");
    printf("╠════════╦══════════════════════════════╦══════╦══════════════════╦═══════════════════╦═══════════════════════╣\n");
    printf("║ %-6s ║ %-28s ║ %-4s ║ %-16s ║ %-17s ║ %-23s ║\n", 
           "Ordem", "Nome do Arquivo", "UID", "Tamanho Original", "Taman. Comprimido", "Modificação");
    printf("╠════════╬══════════════════════════════╬══════╬══════════════════╬═══════════════════╬═══════════════════════╣\n");

    // Exibe informações dos membros
    for (int i = 0; i < qtd_membros; i++) 
    {
        char data_modificacao[20];
        strftime(data_modificacao, sizeof(data_modificacao), "%d/%m/%Y %H:%M", localtime(&membros[i].modificado_em));

        printf("║ %-6d ║ %-28s ║ %-4d ║ %-16ld ║ %-17ld ║ %-21s ║\n",
            membros[i].ordem,
            membros[i].nome,
            membros[i].uid,
            membros[i].tamanho_original,
            membros[i].tamanho_comp,
            data_modificacao);
    }

    printf("╚════════╩══════════════════════════════╩══════╩══════════════════╩═══════════════════╩═══════════════════════╝\n");
    printf("Total de arquivos: %d\n\n", qtd_membros);

    fclose(archive);
    return 0;
}


//============================================================================================================================

// Função que remove os membros indicados de archive
int r_option(char *arquivo, int argc, char *argv[])
{
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // Cria flags de quais manter
    int manter[MAX_MEMBROS];
    for (int i = 0; i < qtd_membros; i++)
        manter[i] = 1;

    // Marca os membros que devem ser removidos
    for (int i = 3; i < argc; i++) 
    {
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(argv[i], membros[j].nome) == 0) 
            {
                manter[j] = 0;
                break;
            }
        }
    }

    // Cria novo arquivo temporário
    FILE *tmp = fopen("temp_archive.bin", "wb");
    if (!tmp) 
    {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(archive);
        return 1;
    }

    int nova_qtd = 0;
    long offset = 0;

    for (int i = 0; i < qtd_membros; i++) 
    {
        if (manter[i]) 
        {
            char *buffer = malloc(membros[i].tamanho_comp);
            fseek(archive, membros[i].offset, SEEK_SET);
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            fseek(tmp, offset, SEEK_SET);
            fwrite(buffer, 1, membros[i].tamanho_comp, tmp);

            membros[nova_qtd] = membros[i];
            membros[nova_qtd].offset = offset;
            membros[nova_qtd].ordem = nova_qtd + 1;
            offset += membros[i].tamanho_comp;
            nova_qtd++;

            free(buffer);
        }
    }

    // Escreve o novo diretório
    long inicio_diretorio = ftell(tmp);
    for (int i = 0; i < nova_qtd; i++) 
    {
        escrever_membro(tmp, &membros[i]);
        imprimir_membro(&membros[i]);
    }

    // Escreve nova quantidade
    fwrite(&nova_qtd, sizeof(int), 1, tmp);

    fclose(archive);
    fclose(tmp);

    // Substitui o arquivo antigo pelo novo
    remove(arquivo);
    rename("temp_archive.bin", arquivo);

    printf("\nMembros removidos com sucesso!\n");
    printf("Novo diretório inicia em: %ld bytes\n", inicio_diretorio);
    printf("Total restante de membros: %d\n", nova_qtd);

    return 0;
}



//============================================================================================================================

// Função que extrai os membros indicados de archive
int x_option(char *arquivo, int argc, char *argv[])
{
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    int extrair_todos = (argc <= 3);

    for (int i = 0; i < qtd_membros; i++) 
    {
        int deve_extrair = extrair_todos;

        if (!extrair_todos) 
        {
            for (int j = 3; j < argc; j++) 
            {
                if (strcmp(argv[j], membros[i].nome) == 0) 
                {
                    deve_extrair = 1;
                    break;
                }
            }
        }

        if (deve_extrair) 
        {
            fseek(archive, membros[i].offset, SEEK_SET);

            // Aloca buffer para os dados no archive
            unsigned char *buffer = malloc(membros[i].tamanho_comp);
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            FILE *f_out = fopen(membros[i].nome, "wb");
            if (!f_out) 
            {
                printf("Erro ao criar '%s'. Pulando...\n", membros[i].nome);
                free(buffer);
                continue;
            }

            if (membros[i].comprimido) 
            {
                // Descomprime
                unsigned char *dados_orig = malloc(membros[i].tamanho_original);
                LZ_Uncompress(buffer, dados_orig, membros[i].tamanho_comp);
                fwrite(dados_orig, 1, membros[i].tamanho_original, f_out);
                free(dados_orig);
            } 
            else 
            {
                // Escreve diretamente
                fwrite(buffer, 1, membros[i].tamanho_original, f_out);
            }

            fclose(f_out);
            free(buffer);

            printf("Extraído: %s\n", membros[i].nome);
        }
    }

    fclose(archive);
    return 0;
}


//============================================================================================================================


// Função que move o membro indicado na linha de comando
int m_option(char *arquivo, int argc, char *argv[])
{
    if (argc < 5) 
    {
        printf("Uso incorreto. Esperado: -m <target|NULL> <membro>\n");
        return 1;
    }

    const char *target = argv[3];
    const char *mover = argv[4];

    Membro membros[MAX_MEMBROS];
    int qtd_membros = 0;

    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        perror("Erro ao abrir o arquivo archive para leitura");
        return 1;
    }

    // Lê a quantidade de membros
    fseek(archive, -sizeof(int), SEEK_END);
    fread(&qtd_membros, sizeof(int), 1, archive);

    // Lê o vetor de membros
    fseek(archive, -(sizeof(int) + qtd_membros * sizeof(Membro)), SEEK_END);
    fread(membros, sizeof(Membro), qtd_membros, archive);

    // Estrutura auxiliar para armazenar dados dos membros
    typedef struct 
    {
        Membro info;
        unsigned char *dados;
    } Registro;

    Registro registros[MAX_MEMBROS];

    for (int i = 0; i < qtd_membros; i++) 
    {
        registros[i].info = membros[i];
        registros[i].dados = malloc(membros[i].tamanho_comp);
        fseek(archive, membros[i].offset, SEEK_SET);
        fread(registros[i].dados, 1, membros[i].tamanho_comp, archive);
    }

    fclose(archive);

    // Identifica índices do membro a mover e do target
    int idx_mover = -1, idx_target = -1;
    for (int i = 0; i < qtd_membros; i++) 
    {
        if (strcmp(registros[i].info.nome, mover) == 0)
            idx_mover = i;
        if (target && strcmp(target, "NULL") != 0 &&
            strcmp(registros[i].info.nome, target) == 0)
            idx_target = i;
    }

    if (idx_mover == -1) 
    {
        printf("Erro: membro '%s' não encontrado no archive.\n", mover);
        return 1;
    }

    // Remove o membro a mover da posição original
    Registro movido = registros[idx_mover];
    for (int i = idx_mover; i < qtd_membros - 1; i++)
        registros[i] = registros[i + 1];

    qtd_membros--;

    // Calcula nova posição
    int nova_pos = (strcmp(target, "NULL") == 0) ? 0 : idx_target + (idx_mover < idx_target ? 0 : 1);

    // Insere o membro movido na nova posição
    for (int i = qtd_membros; i > nova_pos; i--)
        registros[i] = registros[i - 1];

    registros[nova_pos] = movido;
    qtd_membros++;

    // Reescreve o arquivo archive com nova ordem e novos offsets
    archive = fopen(arquivo, "wb");
    if (!archive) 
    {
        perror("Erro ao abrir o arquivo archive para escrita");
        return 1;
    }

    long offset = 0;
    for (int i = 0; i < qtd_membros; i++) 
    {
        registros[i].info.offset = offset;
        registros[i].info.ordem = i + 1;
        fwrite(registros[i].dados, 1, registros[i].info.tamanho_comp, archive);
        offset += registros[i].info.tamanho_comp;
    }

    // Prepara o vetor final de membros
    for (int i = 0; i < qtd_membros; i++) 
    {
        membros[i] = registros[i].info;
        free(registros[i].dados);
    }

    // Grava metadados no final
    fwrite(membros, sizeof(Membro), qtd_membros, archive);
    fwrite(&qtd_membros, sizeof(int), 1, archive);

    fclose(archive);

    printf("Membro '%s' movido com sucesso para após '%s'.\n", mover, target);
    return 0;
}


//============================================================================================================================
/*
    Implementação das funções para o software Arquivador VINAc.
    Desenvolvido por Marcus Neto.
*/

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membro.h"
#include "lz.h"
#include "functions.h"

#define MAX_MEMBROS 1024


/**
 * @brief Tenta abrir um arquivo de archive existente ou criá-lo se não existir.
 * 
 * @param nome_arquivo O nome do arquivo de archive.
 * @return FILE* Ponteiro para o arquivo aberto em modo "r+b" ou "w+b", ou NULL em caso de erro.
 */
FILE* abrir_arquivo(const char *nome_arquivo) 
{
    FILE *archive = fopen(nome_arquivo, "r+b"); // Tenta abrir para leitura e escrita binária
    if (!archive) {
        archive = fopen(nome_arquivo, "w+b"); // Se falhar, tenta criar/abrir para escrita e leitura binária
        if (!archive) {
            printf("Erro: não foi possível criar o arquivo de archive '%s'\n", nome_arquivo);
            return NULL;
        }
    }
    return archive;
}


//============================================================================================================================


//  Função para inserir sem compressão
int p_option(char *arquivo, int argc, char *argv[]) 
{
    Membro membros_existentes[MAX_MEMBROS];
    Membro membros_finais[MAX_MEMBROS];

    // Carrega os membros já existentes do archive
    int qtd_existentes = carregar_membros(arquivo, membros_existentes);

    //Abrir ou criar o arquivo de archive
    FILE *archive = abrir_arquivo(arquivo);
    if (!archive)
        return 1;

    // Regrava no archive os membros antigos que não devem ser substituídos
    int qtd = regravar_membros(archive, membros_existentes, qtd_existentes, argv, argc, membros_finais);

    // Adiciona os novos membros passados na linha de comando
    int qtd_finais = adicionar_membros(archive, argv, argc, qtd, membros_finais);

    // Corrige a ordem dos membros
    for (int i = 0; i < qtd_finais; i++)
        membros_finais[i].ordem = i + 1;

    // Salva o vetor de membros no final do archive
    salvar_membros(archive, membros_finais, qtd_finais);
    fclose(archive);

    return 0;
}



//============================================================================================================================


// Função para inserir arquivos com compressão
int i_option(char *arquivo, int argc, char *argv[]) 
{
    //Abrir ou criar o arquivo de archive
    FILE *archive = abrir_arquivo(arquivo);
    if (!archive)
        return 1;

    Membro membros[MAX_MEMBROS] = {0};  
    int qtd_membros = 0;  
    long file_size = 0;

    if (fseek(archive, 0, SEEK_END) == 0) 
    {
        file_size = ftell(archive);
        rewind(archive);
        if (file_size > 0) 
        {
            qtd_membros = ler_diretorio(archive, membros);
            if (qtd_membros < 0 || qtd_membros > MAX_MEMBROS) 
            {
                printf("Erro ao ler diretório de membros.\n");
                fclose(archive);
                return 1;
            }
        }
    }

    if (fseek(archive, 0, SEEK_END) != 0) 
    {
        printf("Erro ao posicionar ponteiro no final do arquivo.\n");
        fclose(archive);
        return 1;
    }

    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        long tamanho_original = 0;
        if (fseek(f, 0, SEEK_END) != 0 || (tamanho_original = ftell(f)) < 0) 
        {
            printf("Erro ao obter tamanho de '%s'. Pulando...\n", nome_membro);
            fclose(f);
            continue;
        }

        rewind(f);
        char *conteudo_original = malloc(tamanho_original);
        if (!conteudo_original) 
        {
            printf("Erro ao alocar memória para '%s'. Pulando...\n", nome_membro);
            fclose(f);
            continue;
        }

        size_t lido = fread(conteudo_original, 1, tamanho_original, f);
        fclose(f);
        if (lido != (size_t)tamanho_original) 
        {
            printf("Erro ao ler conteúdo de '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            continue;
        }

        char *conteudo_comp = malloc(tamanho_original * 2); 
        if (!conteudo_comp) 
        {
            printf("Erro ao alocar memória para compressão de '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            continue;
        }

        int tamanho_comp = LZ_Compress(
            (unsigned char *)conteudo_original,
            (unsigned char *)conteudo_comp,
            tamanho_original
        );

        int usar_original = (tamanho_comp >= tamanho_original || tamanho_comp <= 0);
        char *dados_finais = usar_original ? conteudo_original : conteudo_comp;
        int tamanho_final = usar_original ? tamanho_original : tamanho_comp;

        if (usar_original)
            printf("Aviso: compressão de [%s] ineficiente. Armazenando arquivo original.\n", nome_membro);

        long offset = ftell(archive);
        if (offset < 0) 
        {
            printf("Erro ao obter offset para '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            free(conteudo_comp);
            continue;
        }

        size_t escrito = fwrite(dados_finais, 1, tamanho_final, archive);
        if (escrito != (size_t)tamanho_final) 
        {
            printf("Erro ao escrever dados de '%s' no archive.\n", nome_membro);
            free(conteudo_original);
            free(conteudo_comp);
            continue;
        }

        // Verifica se o membro já existe e substitui
        int existe = -1;
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[j].nome, nome_membro) == 0) 
            {
                printf("Membro [%s] já existe. Substituindo...\n", nome_membro);
                membros[j].offset = offset;
                membros[j].tamanho_original = tamanho_original;
                membros[j].tamanho_comp = tamanho_final;
                membros[j].modificado_em = time(NULL);
                existe = j;
                break;
            }
        }

        // Se não existe, adiciona novo membro
        if (existe == -1) 
        {
            if (qtd_membros >= MAX_MEMBROS) 
            {
                printf("Erro: número máximo de membros excedido. Ignorando '%s'.\n", nome_membro);
                free(conteudo_original);
                free(conteudo_comp);
                continue;
            }

            Membro m = criar_membro(nome_membro, qtd_membros + 1);
            m.offset = offset;
            m.tamanho_original = tamanho_original;
            m.tamanho_comp = tamanho_final;
            m.modificado_em = time(NULL);
            membros[qtd_membros++] = m;
        }

        free(conteudo_original);
        free(conteudo_comp);
    }

    for (int i = 0; i < qtd_membros; i++) 
        membros[i].ordem = i + 1;

    for (int i = 0; i < qtd_membros; i++) 
        escrever_membro(archive, &membros[i]);

    if (fwrite(&qtd_membros, sizeof(int), 1, archive) != 1) 
    {
        printf("Erro ao escrever quantidade de membros no final do arquivo.\n");
        fclose(archive);
        return 1;
    }

    if (fflush(archive) != 0) 
        printf("Erro ao descarregar buffers para o arquivo.\n");

    fclose(archive);
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
    // Abre o arquivo binário do archive em modo leitura binária
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        // Se não for possível abrir o arquivo, exibe erro e retorna
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    // Vetor para armazenar os metadados dos membros do archive
    Membro membros[MAX_MEMBROS];
    // Lê o diretório do archive e retorna a quantidade de membros
    int qtd_membros = ler_diretorio(archive, membros);

    // Vetor de flags para indicar quais membros devem ser mantidos (1 = manter, 0 = remover)
    int manter[MAX_MEMBROS];

    // Se apenas 3 argumentos foram passados (programa, -r, nome_arquivo), significa que nenhum nome foi passado,
    // então todos os membros devem ser removidos
    if (argc == 3) 
    {
        for (int i = 0; i < qtd_membros; i++)
            manter[i] = 0;
    }
    else 
    {
        // Inicialmente marcamos todos os membros para serem mantidos
        for (int i = 0; i < qtd_membros; i++)
            manter[i] = 1;

        // Para cada argumento extra passado (a partir do índice 3), verificamos se corresponde ao nome de algum membro
        for (int i = 3; i < argc; i++) 
        {
            for (int j = 0; j < qtd_membros; j++) 
            {
                // Se o nome do membro for igual ao argumento passado, marcamos para ser removido
                if (strcmp(argv[i], membros[j].nome) == 0) 
                {
                    manter[j] = 0;
                    break;
                }
            }
        }
    }

    // Cria um novo arquivo temporário onde os membros que devem ser mantidos serão gravados
    FILE *tmp = fopen("temp_archive.bin", "wb");
    if (!tmp) 
    {
        // Se não for possível criar o arquivo temporário, exibe erro, fecha o original e retorna
        printf("Erro ao criar arquivo temporário.\n");
        fclose(archive);
        return 1;
    }

    int nova_qtd = 0;       // Nova quantidade de membros no arquivo
    long offset = 0;        // Posição atual de escrita no arquivo temporário

    // Percorre todos os membros do archive original
    for (int i = 0; i < qtd_membros; i++) 
    {
        if (manter[i]) // Se o membro deve ser mantido
        {
            // Aloca buffer para armazenar os dados do membro
            char *buffer = malloc(membros[i].tamanho_comp);
            
            // Lê os dados do membro do arquivo original
            fseek(archive, membros[i].offset, SEEK_SET);
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            // Escreve os dados no arquivo temporário na posição correta
            fseek(tmp, offset, SEEK_SET);
            fwrite(buffer, 1, membros[i].tamanho_comp, tmp);

            // Atualiza os metadados do membro no novo array
            membros[nova_qtd] = membros[i];          // Copia os metadados
            membros[nova_qtd].offset = offset;       // Atualiza o novo offset no arquivo
            membros[nova_qtd].ordem = nova_qtd + 1;  // Atualiza a ordem (sequencial)
            offset += membros[i].tamanho_comp;       // Atualiza o próximo offset
            nova_qtd++;                              // Incrementa a nova quantidade de membros

            // Libera a memória alocada
            free(buffer);
        }
    }

    // Marca a posição onde começa o novo diretório no arquivo temporário
    long inicio_diretorio = ftell(tmp);

    // Escreve os metadados dos membros restantes no final do arquivo (diretório)
    for (int i = 0; i < nova_qtd; i++) 
    {
        escrever_membro(tmp, &membros[i]);    // Escreve no arquivo
        imprimir_membro(&membros[i]);         // Imprime na tela (opcional/informativo)
    }

    // Escreve a nova quantidade de membros no final do arquivo (após o diretório)
    fwrite(&nova_qtd, sizeof(int), 1, tmp);

    // Fecha os arquivos
    fclose(archive);
    fclose(tmp);

    // Remove o arquivo original e renomeia o temporário como o novo arquivo final
    remove(arquivo);
    rename("temp_archive.bin", arquivo);

    // Mensagem de sucesso e resumo
    printf("\nMembros removidos com sucesso!\n");
    printf("Novo diretório inicia em: %ld bytes\n", inicio_diretorio);
    printf("Total restante de membros: %d\n", nova_qtd);

    return 0; // Sucesso
}



//============================================================================================================================


// Função que extrai os membros indicados de archive
int x_option(char *arquivo, int argc, char *argv[])
{
    // Abre o arquivo de arquivo (archive) no modo binário de leitura
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        // Se não conseguir abrir, exibe erro e encerra
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    // Lê o diretório de membros do arquivo e armazena no vetor 'membros'
    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // Verifica se deve extrair todos os membros (nenhum nome foi passado após o nome do arquivo)
    int extrair_todos = (argc <= 3);

    // Itera por todos os membros do diretório
    for (int i = 0; i < qtd_membros; i++) 
    {
        int deve_extrair = extrair_todos;

        // Se não for para extrair todos, verifica se o nome do membro atual foi passado na linha de comando
        if (!extrair_todos) 
        {
            for (int j = 3; j < argc; j++) 
            {
                if (strcmp(argv[j], membros[i].nome) == 0) 
                {
                    // Marca para extração se o nome do membro corresponder
                    deve_extrair = 1;
                    break;
                }
            }
        }

        // Se for para extrair esse membro
        if (deve_extrair) 
        {
            // Move o ponteiro do arquivo para a posição do dado compactado
            fseek(archive, membros[i].offset, SEEK_SET);

            // Aloca um buffer com o tamanho dos dados compactados e lê os dados
            unsigned char *buffer = malloc(membros[i].tamanho_comp);
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            // Abre o arquivo de saída com o nome do membro
            FILE *f_out = fopen(membros[i].nome, "wb");
            if (!f_out) 
            {
                // Caso falhe ao criar o arquivo de saída, exibe erro e pula para o próximo membro
                printf("Erro ao criar '%s'. Pulando...\n", membros[i].nome);
                free(buffer);
                continue;
            }

            // Verifica se o membro está compactado
            if (membros[i].comprimido) 
            {
                // Se estiver, aloca espaço para os dados originais e descompacta
                unsigned char *dados_orig = malloc(membros[i].tamanho_original);
                LZ_Uncompress(buffer, dados_orig, membros[i].tamanho_comp);

                // Escreve os dados descompactados no arquivo de saída
                fwrite(dados_orig, 1, membros[i].tamanho_original, f_out);
                free(dados_orig);
            } 
            else 
            {
                // Se não estiver compactado, escreve os dados diretamente
                fwrite(buffer, 1, membros[i].tamanho_original, f_out);
            }

            // Fecha o arquivo de saída e libera o buffer
            fclose(f_out);
            free(buffer);

            // Informa que o membro foi extraído com sucesso
            printf("Extraído: %s\n", membros[i].nome);
        }
    }

    // Fecha o arquivo principal
    fclose(archive);
    return 0;
}



//============================================================================================================================


// Função que move o membro indicado na linha de comando
int m_option(char *arquivo, int argc, char *argv[])
{
    // Verifica se o número de argumentos é suficiente
    if (argc < 5) 
    {
        printf("Uso incorreto. Esperado: -m <target|NULL> <membro>\n");
        return 1;
    }

    // Define o membro alvo (após quem será inserido) e o membro a ser movido
    const char *target = argv[3];
    const char *mover = argv[4];

    Membro membros[MAX_MEMBROS];
    int qtd_membros = 0;

    // Abre o arquivo do archive para leitura binária
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        perror("Erro ao abrir o arquivo archive para leitura");
        return 1;
    }

    // Lê a quantidade de membros no final do arquivo
    fseek(archive, -sizeof(int), SEEK_END);
    fread(&qtd_membros, sizeof(int), 1, archive);

    // Lê o vetor de metadados dos membros
    fseek(archive, -(sizeof(int) + qtd_membros * sizeof(Membro)), SEEK_END);
    fread(membros, sizeof(Membro), qtd_membros, archive);

    // Define uma estrutura auxiliar para armazenar dados de cada membro
    typedef struct 
    {
        Membro info;               // Metadados do membro
        unsigned char *dados;      // Conteúdo binário do membro
    } Registro;

    Registro registros[MAX_MEMBROS];

    // Carrega os dados de todos os membros do arquivo
    for (int i = 0; i < qtd_membros; i++) 
    {
        registros[i].info = membros[i];
        registros[i].dados = malloc(membros[i].tamanho_comp);  // Aloca espaço para os dados
        fseek(archive, membros[i].offset, SEEK_SET);           // Vai para a posição do dado no arquivo
        fread(registros[i].dados, 1, membros[i].tamanho_comp, archive);  // Lê os dados
    }

    fclose(archive);  // Fecha o arquivo após leitura

    // Encontra os índices do membro a mover e do membro alvo
    int idx_mover = -1, idx_target = -1;
    for (int i = 0; i < qtd_membros; i++) 
    {
        if (strcmp(registros[i].info.nome, mover) == 0)
            idx_mover = i;

        // Se o target não for "NULL", compara com os nomes
        if (target && strcmp(target, "NULL") != 0 &&
            strcmp(registros[i].info.nome, target) == 0)
            idx_target = i;
    }

    // Se o membro a ser movido não foi encontrado, aborta
    if (idx_mover == -1) 
    {
        printf("Erro: membro '%s' não encontrado no archive.\n", mover);
        return 1;
    }

    // Remove o membro da posição original (desloca os outros para preencher o espaço)
    Registro movido = registros[idx_mover];
    for (int i = idx_mover; i < qtd_membros - 1; i++)
        registros[i] = registros[i + 1];

    qtd_membros--;  // Reduz a quantidade temporariamente

    // Calcula a nova posição do membro
    // Se target for "NULL", o membro será inserido no início
    // Se mover estava antes do target, ele será inserido exatamente onde o target estava
    // Caso contrário, será inserido uma posição à frente
    int nova_pos = (strcmp(target, "NULL") == 0) ? 0 : idx_target + (idx_mover < idx_target ? 0 : 1);

    // Insere o membro na nova posição (desloca os outros para abrir espaço)
    for (int i = qtd_membros; i > nova_pos; i--)
        registros[i] = registros[i - 1];

    registros[nova_pos] = movido;  // Coloca o membro na nova posição
    qtd_membros++;                 // Atualiza a quantidade de membros

    // Reabre o arquivo para escrita binária (vai sobrescrever tudo)
    archive = fopen(arquivo, "wb");
    if (!archive) 
    {
        perror("Erro ao abrir o arquivo archive para escrita");
        return 1;
    }

    // Escreve os dados dos membros na nova ordem e atualiza os offsets
    long offset = 0;
    for (int i = 0; i < qtd_membros; i++) 
    {
        registros[i].info.offset = offset;                 // Define novo offset
        registros[i].info.ordem = i + 1;                   // Atualiza ordem
        fwrite(registros[i].dados, 1, registros[i].info.tamanho_comp, archive);  // Grava os dados
        offset += registros[i].info.tamanho_comp;          // Atualiza o offset para o próximo
    }

    // Atualiza o vetor de membros com os novos metadados e libera memória
    for (int i = 0; i < qtd_membros; i++) 
    {
        membros[i] = registros[i].info;
        free(registros[i].dados);  // Libera a memória alocada para os dados
    }

    // Grava os metadados dos membros ao final do arquivo
    fwrite(membros, sizeof(Membro), qtd_membros, archive);
    fwrite(&qtd_membros, sizeof(int), 1, archive);  // Grava a quantidade total de membros

    fclose(archive);  // Fecha o arquivo

    // Mensagem de sucesso
    printf("Membro '%s' movido com sucesso para após '%s'.\n", mover, target);
    return 0;
}


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
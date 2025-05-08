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
int p_option(char *arquivo, int argc, char *argv[]) 
{
    // Declara um vetor para armazenar membros já existentes no arquivo
    Membro membros_existentes[MAX_MEMBROS];
    int qtd_existentes = 0;

    // Tenta abrir o arquivo de archive existente para leitura binária
    FILE *archive = fopen(arquivo, "rb");
    if (archive) 
    {
        // Move o ponteiro para os últimos 4 bytes do arquivo (onde está armazenado o número de membros)
        fseek(archive, -sizeof(int), SEEK_END);
        // Lê a quantidade de membros existentes no final do arquivo
        fread(&qtd_existentes, sizeof(int), 1, archive);

        // Volta até onde começa o vetor de membros no arquivo
        fseek(archive, -(sizeof(int) + qtd_existentes * sizeof(Membro)), SEEK_END);
        // Lê o vetor de membros existentes do arquivo
        fread(membros_existentes, sizeof(Membro), qtd_existentes, archive);

        // Fecha o arquivo após leitura
        fclose(archive);
    }

    // Reabre o arquivo em modo de escrita binária, sobrescrevendo o conteúdo
    archive = fopen(arquivo, "wb");
    if (!archive) 
    {
        // Se falhar ao abrir para escrita, exibe mensagem de erro
        printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
        return 1;
    }

    // Vetor para armazenar os membros finais (após substituições)
    Membro membros_finais[MAX_MEMBROS];
    int qtd_finais = 0;

    // Verifica cada membro existente para ver se deve ser mantido ou substituído
    for (int i = 0; i < qtd_existentes; i++) 
    {
        int substituir = 0;
        // Verifica se o nome do membro existente aparece nos novos argumentos (para substituição)
        for (int j = 3; j < argc; j++) 
        {
            if (strcmp(membros_existentes[i].nome, argv[j]) == 0) 
            {
                printf("Membro '%s' já existe. Substituindo...\n", argv[j]);
                substituir = 1;
                break;
            }
        }

        // Se não for substituído, regrava o conteúdo do membro existente no novo arquivo
        if (!substituir) 
        {
            FILE *f = fopen(membros_existentes[i].nome, "rb");
            if (!f) 
            {
                printf("Aviso: não foi possível reabrir '%s'. Pulando...\n", membros_existentes[i].nome);
                continue;
            }

            // Copia os dados do membro para o novo arquivo
            Membro m = membros_existentes[i];
            m.offset = ftell(archive);   // Atualiza a posição (offset) no novo arquivo
            m.comprimido = 0;            // Indica que o membro não está comprimido

            char buffer[1024] = {0};     // Buffer temporário para leitura e escrita
            size_t lidos;
            fseek(f, 0, SEEK_SET);       // Garante que a leitura começa do início
            while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0)
                fwrite(buffer, 1, lidos, archive);

            fclose(f);
            membros_finais[qtd_finais++] = m; // Adiciona o membro à lista final
        }
    }

    // Adiciona os novos membros (inclusive os que substituem existentes)
    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        // Cria um novo membro a partir do arquivo
        Membro m = criar_membro(nome_membro, qtd_finais + 1);
        m.offset = ftell(archive);   // Define onde os dados do membro serão armazenados
        m.comprimido = 0;            // Sem compressão

        char buffer[1024] = {0};     // Buffer para leitura e escrita
        size_t lidos;
        while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0)
            fwrite(buffer, 1, lidos, archive);

        fclose(f);
        membros_finais[qtd_finais++] = m; // Adiciona o novo membro à lista final
    }

    // Ajusta os campos 'ordem' de cada membro para garantir sequência correta
    for (int i = 0; i < qtd_finais; i++)
        membros_finais[i].ordem = i + 1;

    // Escreve o vetor de membros no final do arquivo
    fwrite(membros_finais, sizeof(Membro), qtd_finais, archive);

    // Escreve a quantidade total de membros como último valor no arquivo
    fwrite(&qtd_finais, sizeof(int), 1, archive);

    // Fecha o arquivo archive após gravação
    fclose(archive);

    // Mensagem de sucesso e exibição dos membros incluídos
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
    // Tenta abrir o arquivo de archive para leitura e escrita binária
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        // Se não existir, cria o arquivo
        archive = fopen(arquivo, "w+b");
        if (!archive) 
        {
            printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
            return 1;
        }
    }

    // Lê o diretório existente de membros (caso haja)
    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // Move o ponteiro para o final do arquivo para começar a adicionar novos dados
    fseek(archive, 0, SEEK_END);

    // Percorre os arquivos passados como argumentos (a partir de argv[3])
    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        
        // Tenta abrir o arquivo do membro a ser adicionado
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        // Determina o tamanho do arquivo original
        fseek(f, 0, SEEK_END);
        long tamanho_original = ftell(f);
        rewind(f);

        // Lê o conteúdo completo do arquivo original
        char *conteudo_original = malloc(tamanho_original);
        fread(conteudo_original, 1, tamanho_original, f);
        fclose(f);

        // Aloca memória para o conteúdo comprimido
        char *conteudo_comp = malloc(tamanho_original * 2); // espaço extra para compressão
        int tamanho_comp = LZ_Compress(
            (unsigned char *)conteudo_original,
            (unsigned char *)conteudo_comp,
            tamanho_original
        );

        // Verifica se a compressão foi eficiente
        int usar_original = (tamanho_comp >= tamanho_original);
        char *dados_finais = usar_original ? conteudo_original : conteudo_comp;
        int tamanho_final = usar_original ? tamanho_original : tamanho_comp;

        // Exibe aviso se compressão não for vantajosa
        if (usar_original)
            printf("Aviso: compressão de '%s' ineficiente. Armazenando arquivo original.\n", nome_membro);

        // Verifica se o membro já existe no diretório
        int existe = -1;
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[j].nome, nome_membro) == 0) 
            {
                existe = j;
                break;
            }
        }

        // Marca o offset atual no arquivo (onde os dados do membro começarão)
        long offset = ftell(archive);

        // Escreve os dados finais (originais ou comprimidos) no arquivo
        fwrite(dados_finais, 1, tamanho_final, archive);

        // Libera memória alocada
        free(conteudo_original);
        free(conteudo_comp);

        if (existe != -1) 
        {
            // Se o membro já existia, atualiza seus dados
            printf("Membro '%s' já existe. Substituindo...\n", nome_membro);
            membros[existe].offset = offset;
            membros[existe].tamanho_original = tamanho_original;
            membros[existe].tamanho_comp = tamanho_final;
            membros[existe].modificado_em = time(NULL);
            membros[existe].comprimido = !usar_original;
        } 
        else 
        {
            // Caso contrário, cria um novo membro e adiciona ao vetor
            Membro m = criar_membro(nome_membro, qtd_membros + 1);
            m.offset = offset;
            m.tamanho_original = tamanho_original;
            m.tamanho_comp = tamanho_final;
            m.modificado_em = time(NULL);
            m.comprimido = !usar_original;
            membros[qtd_membros++] = m;
        }
    }

    // Atualiza o campo de ordem de todos os membros
    for (int i = 0; i < qtd_membros; i++) 
        membros[i].ordem = i + 1;

    printf("\nArchive criado com sucesso!\n");
    printf("Total de membros: %d\n", qtd_membros);

    // Marca o ponto onde começa o novo diretório
    long inicio_diretorio = ftell(archive);

    // Escreve as informações de cada membro no final do arquivo
    for (int i = 0; i < qtd_membros; i++) 
    {
        escrever_membro(archive, &membros[i]);  // grava metadados
        imprimir_membro(&membros[i]);           // exibe metadados no terminal
    }

    // Grava a quantidade total de membros no final do arquivo
    fwrite(&qtd_membros, sizeof(int), 1, archive);
    fclose(archive);  // Fecha o arquivo

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
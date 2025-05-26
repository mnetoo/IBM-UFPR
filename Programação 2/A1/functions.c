/*
    Implementação das funções para o software Arquivador VINAc.
    Desenvolvido por Marcus Neto.
*/
#include "membro.h"
#include "lz.h"
#include "functions.h"


//  Função que obtém o UID do usuário atual
int obter_uid() 
{
    return getuid();  // pega UID do usuário atual
}


//============================================================================================================================


//  Função para inserir/atualizar arquivos sem compressão em um archive
// Parâmetros:
// - arquivo: nome do arquivo archive
// - argc: contagem de argumentos da linha de comando
// - argv: array de argumentos da linha de comando
int p_option(char *arquivo, int argc, char *argv[])
{
    Membro membros[MAX_MEMBROS];
    int qtd_membros = 0;

    // 1. Determinar o maior tamanho de arquivo passado via argv
    long max_tamanho = 0;
    for (int i = 3; i < argc; i++) 
    {
        FILE *f = fopen(argv[i], "rb");
        if (f) 
        {
            fseek(f, 0, SEEK_END);
            long size = ftell(f);
            if (size > max_tamanho) max_tamanho = size;
            fclose(f);
        }
    }

    char *buffer = malloc(max_tamanho);
    if (!buffer) 
    {
        printf("Erro ao alocar buffer de %ld bytes.\n", max_tamanho);
        return 1;
    }

    // 2. Abrir o archive e carregar membros (somente metadados)
    FILE *archive = fopen(arquivo, "r+b");
    if (archive) 
    {
        fseek(archive, -sizeof(int), SEEK_END);
        fread(&qtd_membros, sizeof(int), 1, archive);

        long offset_membros = -(sizeof(int) + qtd_membros * sizeof(Membro));
        fseek(archive, offset_membros, SEEK_END);
        fread(membros, sizeof(Membro), qtd_membros, archive);
    } 
    else 
    {
        archive = fopen(arquivo, "w+b");
        if (!archive) 
        {
            printf("Erro ao criar '%s'\n", arquivo);
            free(buffer);
            return 1;
        }
    }

    // 3. Processar cada argumento
    for (int a = 3; a < argc; a++) 
    {
        char *nome = argv[a];
        FILE *f = fopen(nome, "rb");
        if (!f) 
        {
            printf("Erro ao abrir '%s'\n", nome);
            continue;
        }

        fseek(f, 0, SEEK_END);
        long tamanho_novo = ftell(f);
        rewind(f);

        fread(buffer, 1, tamanho_novo, f);
        fclose(f);

        // Verificar se o membro já existe
        int pos = -1;
        for (int i = 0; i < qtd_membros; i++) 
        {
            if (strcmp(membros[i].nome, nome) == 0) 
            {
                pos = i;
                break;
            }
        }

        if (pos != -1) 
        {
            // Membro já existe
            Membro *m = &membros[pos];

            if (tamanho_novo <= m->tamanho_original) 
            {
                // Substituição direta
                fseek(archive, m->offset, SEEK_SET);
                fwrite(buffer, 1, tamanho_novo, archive);
                m->tamanho_original = tamanho_novo;
                m->tamanho_comp = tamanho_novo;

                // Compactação não utilizada
                m->comprimido = 0;

                // Atualizar os dados dos membros seguintes
                long diff = m->tamanho_original - tamanho_novo;
                if (diff > 0) 
                {
                    for (int i = pos + 1; i < qtd_membros; i++) 
                    {
                        char *tmp = malloc(membros[i].tamanho_original);
                        fseek(archive, membros[i].offset, SEEK_SET);
                        fread(tmp, 1, membros[i].tamanho_original, archive);
                        membros[i].offset -= diff;
                        fseek(archive, membros[i].offset, SEEK_SET);
                        fwrite(tmp, 1, membros[i].tamanho_original, archive);
                        free(tmp);
                    }
                }
            } 
            else 
            {
                // Novo arquivo é maior, realocar os seguintes
                long nova_pos = m->offset + tamanho_novo;

                // Realocar todos os membros após o atual
                for (int i = qtd_membros - 1; i > pos; i--) 
                {
                    char *tmp = malloc(membros[i].tamanho_original);
                    fseek(archive, membros[i].offset, SEEK_SET);
                    fread(tmp, 1, membros[i].tamanho_original, archive);
                    membros[i].offset = nova_pos;
                    fseek(archive, membros[i].offset, SEEK_SET);
                    fwrite(tmp, 1, membros[i].tamanho_original, archive);
                    nova_pos += membros[i].tamanho_original;
                    free(tmp);
                }

                // Escrever o novo dado do membro
                fseek(archive, m->offset, SEEK_SET);
                fwrite(buffer, 1, tamanho_novo, archive);
                m->tamanho_original = tamanho_novo;
                m->tamanho_comp = tamanho_novo;
                m->comprimido = 0;
            }

        } 
        else 
        {
            // Novo membro
            Membro m = criar_membro(nome, qtd_membros + 1);
            fseek(archive, 0, SEEK_END);
            m.offset = ftell(archive);
            m.tamanho_original = tamanho_novo;
            m.tamanho_comp = tamanho_novo;
            m.comprimido = 0;
            fwrite(buffer, 1, tamanho_novo, archive);
            membros[qtd_membros++] = m;
        }
    }

    // 4. Recalcula a ordem/número dos membros
    for (int i = 0; i < qtd_membros; i++) 
        membros[i].ordem = i + 1;

    // 5. Escrever metadados atualizados
    fseek(archive, 0, SEEK_END);
    fwrite(membros, sizeof(Membro), qtd_membros, archive);
    fwrite(&qtd_membros, sizeof(int), 1, archive);

    fclose(archive);
    free(buffer);
    return 0;
}


//============================================================================================================================


// Função para inserir/atualizar arquivos com compressão em um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos a inserir)
int i_option(char *arquivo, int argc, char *argv[]) 
{
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        // Se o arquivo não existir, crie um novo
        archive = fopen(arquivo, "w+b");
        if (!archive) 
        {
            printf("Erro ao criar o arquivo de archive '%s'\n", arquivo);
            return 1;
        }
    }

    // 1. Ler metadados existentes
    Membro membros[MAX_MEMBROS];
    int qtd_membros = 0;
    fseek(archive, 0, SEEK_END);
    size_t tamanho_archive = ftell(archive);

    if (tamanho_archive >= sizeof(int)) 
    {
        // Verifica se há metadados
        fseek(archive, -sizeof(int), SEEK_END);
        fread(&qtd_membros, sizeof(int), 1, archive);

        if (qtd_membros > 0 && qtd_membros <= MAX_MEMBROS) 
        {
            fseek(archive, -(sizeof(int) + qtd_membros * sizeof(Membro)), SEEK_END);
            fread(membros, sizeof(Membro), qtd_membros, archive);
        } 
        else
            qtd_membros = 0;
    }

    // 2. Determinar o maior tamanho de arquivo de entrada
    size_t maior_tamanho = 0;
    for (int i = 3; i < argc; i++) 
    {
        FILE *f = fopen(argv[i], "rb");
        if (!f) 
        {
            printf("Erro ao abrir '%s'\n", argv[i]);
            continue;
        }
        fseek(f, 0, SEEK_END);
        size_t tamanho = ftell(f);
        if (tamanho > maior_tamanho) maior_tamanho = tamanho;
        fclose(f);
    }

    if (maior_tamanho == 0) 
    {
        printf("Nenhum arquivo válido para inserir.\n");
        fclose(archive);
        return 1;
    }

    // 3. Alocar buffers
    char *buffer_entrada = malloc(maior_tamanho);
    char *buffer_saida = malloc(maior_tamanho * 2); // Espaço para dados comprimidos
    if (!buffer_entrada || !buffer_saida) 
    {
        printf("Erro de alocação de memória.\n");
        free(buffer_entrada);
        free(buffer_saida);
        fclose(archive);
        return 1;
    }

    // 4. Processar cada arquivo de entrada
    for (int i = 3; i < argc; i++) 
    {
        FILE *f = fopen(argv[i], "rb");
        if (!f) {
            printf("Erro ao abrir '%s'\n", argv[i]);
            continue;
        }

        // Ler dados do arquivo
        fseek(f, 0, SEEK_END);
        size_t tamanho_original = ftell(f);
        rewind(f);
        fread(buffer_entrada, 1, tamanho_original, f);
        fclose(f);

        // Comprimir dados
        size_t tamanho_comprimido = LZ_Compress((unsigned char *)buffer_entrada, (unsigned char *)buffer_saida, (unsigned int)tamanho_original);

        // Decidir se armazena comprimido ou não
        char *dados_para_armazenar;
        size_t tamanho_para_armazenar;
        int comprimido;
        if (tamanho_comprimido < tamanho_original) 
        {
            dados_para_armazenar = buffer_saida;
            tamanho_para_armazenar = tamanho_comprimido;
            comprimido = 1;
        } 
        else 
        {
            dados_para_armazenar = buffer_entrada;
            tamanho_para_armazenar = tamanho_original;
            comprimido = 0;
        }

        // Verificar se o membro já existe
        int indice_existente = -1;
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[j].nome, argv[i]) == 0) 
            {
                indice_existente = j;
                break;
            }
        }

        if (indice_existente != -1) 
        {
            // Substituir membro existente
            Membro *m = &membros[indice_existente];
            if (tamanho_para_armazenar <= (size_t)m->tamanho_comp) 
            {
                // Sobrescrever no mesmo local
                fseek(archive, m->offset, SEEK_SET);
                fwrite(dados_para_armazenar, 1, tamanho_para_armazenar, archive);
        
                // Preencher o restante com zeros, se necessário
                size_t restante = m->tamanho_comp - tamanho_para_armazenar;
                if (restante > 0) 
                {
                    char *zeros = calloc(1, restante);
                    fwrite(zeros, 1, restante, archive);
                    free(zeros);
                }
        
                // Atualizar metadados corretamente
                m->tamanho_original = (int)tamanho_original;
                m->tamanho_comp = (int)tamanho_para_armazenar;
                m->comprimido = comprimido;
        
            } 
            else 
            {
                // Reescrever membros subsequentes
                size_t deslocamento = tamanho_para_armazenar - m->tamanho_comp;

                for (int j = qtd_membros - 1; j > indice_existente; j--) 
                {
                    Membro *mj = &membros[j];
                    char *temp = malloc(mj->tamanho_comp);
                    fseek(archive, mj->offset, SEEK_SET);
                    fread(temp, 1, mj->tamanho_comp, archive);
                    mj->offset += deslocamento;
                    fseek(archive, mj->offset, SEEK_SET);
                    fwrite(temp, 1, mj->tamanho_comp, archive);
                    free(temp);
                }

                // Escrever novo membro
                fseek(archive, m->offset, SEEK_SET);
                fwrite(dados_para_armazenar, 1, tamanho_para_armazenar, archive);

                // Atualizar metadados corretamente
                m->tamanho_original = (int)tamanho_original;
                m->tamanho_comp = (int)tamanho_para_armazenar;
                m->comprimido = comprimido;
            }
        } 
        else 
        {
            // Adicionar novo membro
            Membro novo;
            strncpy(novo.nome, argv[i], sizeof(novo.nome));
            novo.nome[sizeof(novo.nome) - 1] = '\0';
            novo.offset = tamanho_archive;
            novo.tamanho_original = tamanho_original;
            novo.tamanho_comp = tamanho_para_armazenar;
            novo.comprimido = comprimido;
            novo.ordem = qtd_membros + 1;
            fseek(archive, tamanho_archive, SEEK_SET);
            fwrite(dados_para_armazenar, 1, tamanho_para_armazenar, archive);
            membros[qtd_membros++] = novo;
            tamanho_archive += tamanho_para_armazenar;
        }
    }

    // 5. Recalcular ordem dos membros
    for (int i = 0; i < qtd_membros; i++)
        membros[i].ordem = i + 1;

    // 6. Escrever metadados atualizados
    fseek(archive, 0, SEEK_END);
    fwrite(membros, sizeof(Membro), qtd_membros, archive);
    fwrite(&qtd_membros, sizeof(int), 1, archive);

    // 7. Liberar recursos
    free(buffer_entrada);
    free(buffer_saida);
    fclose(archive);

    return 0;
}


//============================================================================================================================


// Função para listar os membros do archive
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


// Função para remover arquivos de um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos a remover)
int r_option(char *arquivo, int argc, char *argv[]) 
{
    // 1. ABERTURA DO ARCHIVE
    // Tenta abrir o archive em modo leitura/escrita binária
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    // 2. LEITURA DO DIRETÓRIO ATUAL
    // Array para armazenar informações dos membros existentes
    Membro membros[MAX_MEMBROS];
    // Lê o diretório de membros do archive
    int qtd_membros = ler_diretorio(archive, membros);

    // 3. IDENTIFICAÇÃO DOS ARQUIVOS A MANTER/REMOVER
    // Array para marcar quais membros devem ser mantidos (1) ou removidos (0)
    int manter[MAX_MEMBROS];
    
    // Caso 1: Se apenas 'r' foi passado (sem arquivos específicos)
    if (argc == 3) 
    {
        // Remove todos os arquivos (marca todos para não manter)
        for (int i = 0; i < qtd_membros; i++) 
            manter[i] = 0;
    } 
    else 
    {
        // Caso 2: Com arquivos específicos para remover
        // Primeiro marca todos para manter
        for (int i = 0; i < qtd_membros; i++) 
            manter[i] = 1;
        
        // Depois desmarca os que devem ser removidos
        for (int i = 3; i < argc; i++) 
        {
            for (int j = 0; j < qtd_membros; j++) 
            {
                if (strcmp(argv[i], membros[j].nome) == 0) 
                {
                    manter[j] = 0;  // Marca para remoção
                    break;
                }
            }
        }
    }

    // 4. PREPARAÇÃO PARA RECONSTRUÇÃO DO ARCHIVE
    // Encontra o maior tamanho entre os membros que serão mantidos
    // (para alocar um buffer de tamanho adequado)
    long maior_tam = 0;
    for (int i = 0; i < qtd_membros; i++)
    {
        if (manter[i] && membros[i].tamanho_comp > maior_tam)
            maior_tam = membros[i].tamanho_comp;
    }

    // Aloca buffer com tamanho do maior membro a ser mantido
    char *buffer = malloc(maior_tam);
    if (!buffer) 
    {
        perror("Erro ao alocar buffer");
        fclose(archive);
        return 1;
    }

    // 5. RECONSTRUÇÃO DO ARCHIVE
    long offset_atual = 0;  // Controla a posição atual no novo archive
    int nova_qtd = 0;       // Contador de membros no novo archive

    for (int i = 0; i < qtd_membros; i++) 
    {
        if (manter[i]) {
            // 5.1 LÊ O MEMBRO DO ARCHIVE ORIGINAL
            fseek(archive, membros[i].offset, SEEK_SET);
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            // 5.2 ESCREVE NA NOVA POSIÇÃO (compactando o archive)
            fseek(archive, offset_atual, SEEK_SET);
            fwrite(buffer, 1, membros[i].tamanho_comp, archive);

            // 5.3 ATUALIZA OS METADADOS DO MEMBRO
            membros[nova_qtd] = membros[i];           // Copia os dados
            membros[nova_qtd].offset = offset_atual;  // Atualiza offset
            membros[nova_qtd].ordem = nova_qtd + 1;   // Atualiza ordem

            // 5.4 ATUALIZA CONTADORES
            offset_atual += membros[i].tamanho_comp;  // Avança o offset
            nova_qtd++;                               // Incrementa contador
        }
    }

    // 6. ESCRITA DO NOVO DIRETÓRIO
    // Posiciona no final dos dados compactados
    fseek(archive, offset_atual, SEEK_SET);

    // Escreve todos os membros mantidos no diretório
    for (int i = 0; i < nova_qtd; i++) 
        escrever_membro(archive, &membros[i]);

    // Escreve a nova quantidade de membros no final
    fwrite(&nova_qtd, sizeof(int), 1, archive);

    // 7. AJUSTE FINAL DO TAMANHO DO ARQUIVO
    // Obtém a posição final do archive
    long final_pos = ftell(archive);
    fflush(archive);
    
    // Trunca o arquivo para remover espaço não utilizado
    #if defined(_WIN32)
        _chsize(_fileno(archive), final_pos);  // Windows
    #else
        ftruncate(fileno(archive), final_pos); // Linux/Unix
    #endif

    // 8. LIMPEZA E FINALIZAÇÃO
    free(buffer);     // Libera o buffer temporário
    fclose(archive);  // Fecha o archive

    return 0;  // Retorna sucesso
}


//============================================================================================================================


// Função para extrair arquivos de um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos específicos a extrair)
int x_option(char *arquivo, int argc, char *argv[])
{
    // 1. ABERTURA DO ARCHIVE
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    // 2. LEITURA DO DIRETÓRIO
    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // 3. VERIFICAÇÃO DE ARGUMENTOS
    int extrair_todos = (argc <= 3);

    // 4. PREPARAÇÃO DO BUFFER
    long maior_tam = 0;
    for (int i = 0; i < qtd_membros; i++)
    {
        if (membros[i].tamanho_comp > maior_tam)
            maior_tam = membros[i].tamanho_comp;
    }

    if (maior_tam <= 0) {
        printf("Erro: nenhum membro válido encontrado para alocar buffer\n");
        fclose(archive);
        return 1;
    }

    unsigned char *buffer = malloc(maior_tam);
    if (!buffer) 
    {
        printf("Erro ao alocar memória\n");
        fclose(archive);
        return 1;
    }

    // 5. PROCESSAMENTO DOS MEMBROS
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
            if (membros[i].tamanho_comp > maior_tam) {
                printf("Erro: tamanho_comp do membro '%s' maior que buffer alocado. Pulando...\n", membros[i].nome);
                continue;
            }

            fseek(archive, membros[i].offset, SEEK_SET);

            size_t lidos = fread(buffer, 1, membros[i].tamanho_comp, archive);
            if (lidos != (size_t)membros[i].tamanho_comp) {
                printf("Erro ao ler dados do membro '%s'. Pulando...\n", membros[i].nome);
                continue;
            }

            FILE *f_out = fopen(membros[i].nome, "wb");
            if (!f_out) 
            {
                printf("Erro ao criar '%s'. Pulando...\n", membros[i].nome);
                continue;
            }

            if (membros[i].comprimido) 
            {
                if (membros[i].tamanho_original <= 0) {
                    printf("Erro: tamanho_original inválido para '%s'. Pulando...\n", membros[i].nome);
                    fclose(f_out);
                    continue;
                }

                unsigned char *saida = malloc(membros[i].tamanho_original);
                if (!saida) 
                {
                    printf("Erro ao alocar memória para descompressão de '%s'\n", membros[i].nome);
                    fclose(f_out);
                    continue;
                }

                LZ_Uncompress(buffer, saida, membros[i].tamanho_comp);

                fwrite(saida, 1, membros[i].tamanho_original, f_out);

                free(saida);
            } 
            else 
            {
                fwrite(buffer, 1, membros[i].tamanho_original, f_out);
            }

            fclose(f_out);
        }
    }

    free(buffer);
    fclose(archive);
    return 0;
}


//============================================================================================================================


// Função para mover/reordenar membros dentro do archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos
//   [3]: target (membro de referência ou "NULL" para início)
//   [4]: mover (membro a ser movido)
int m_option(char *arquivo, int argc, char *argv[])
{
    if (argc < 5) 
    {
        printf("Uso incorreto. Esperado: -m <target|NULL> <membro>\n");
        return 1;
    }

    const char *target = argv[3];
    const char *mover = argv[4];

    FILE *f = fopen(arquivo, "rb+");
    if (!f) 
    {
        perror("Erro ao abrir o arquivo archive");
        return 1;
    }

    Membro membros[MAX_MEMBROS];
    Membro membros_originais[MAX_MEMBROS];
    int qtd_membros = 0;

    // Lê diretório e quantidade
    if (fseek(f, -sizeof(int), SEEK_END) != 0 ||
        fread(&qtd_membros, sizeof(int), 1, f) != 1 ||
        fseek(f, -(sizeof(int) + qtd_membros * sizeof(Membro)), SEEK_END) != 0 ||
        fread(membros, sizeof(Membro), qtd_membros, f) != (size_t)qtd_membros) 
    {
        perror("Erro ao ler dados do arquivo");
        fclose(f);
        return 1;
    }

    // Cópia dos membros com offsets originais
    memcpy(membros_originais, membros, sizeof(Membro) * qtd_membros);

    int idx_mover = -1, idx_target = -1;
    for (int i = 0; i < qtd_membros; i++) 
    {
        if (strcmp(membros[i].nome, mover) == 0)
            idx_mover = i;

        if (target && strcmp(target, "NULL") != 0 && strcmp(membros[i].nome, target) == 0)
            idx_target = i;
    }

    if (idx_mover == -1) 
    {
        printf("Erro: membro '%s' não encontrado no archive.\n", mover);
        fclose(f);
        return 1;
    }

    if (target && strcmp(target, "NULL") != 0 && idx_target == -1) 
    {
        printf("Erro: membro target '%s' não encontrado no archive.\n", target);
        fclose(f);
        return 1;
    }

    int nova_pos = (target && strcmp(target, "NULL") == 0) ? 0 : idx_target + (idx_mover < idx_target ? 0 : 1);
    if (nova_pos == idx_mover) 
    {
        printf("Membro já está na posição desejada.\n");
        fclose(f);
        return 0;
    }

    Membro mover_membro = membros[idx_mover];

    if (idx_mover < nova_pos) 
    {
        for (int i = idx_mover; i < nova_pos - 1; i++)
            membros[i] = membros[i + 1];
        membros[nova_pos - 1] = mover_membro;
    } 
    else 
    {
        for (int i = idx_mover; i > nova_pos; i--)
            membros[i] = membros[i - 1];
        membros[nova_pos] = mover_membro;
    }

    // Logo após memcpy dos membros_originais
    size_t maior_tamanho = 0;
    for (int i = 0; i < qtd_membros; i++)
        if ((size_t)membros[i].tamanho_comp > maior_tamanho)
            maior_tamanho = (size_t)membros[i].tamanho_comp;

    unsigned char *buffer = malloc(maior_tamanho);
    if (!buffer) 
    {
        perror("malloc falhou");
        fclose(f);
        return 1;
    }

    // Reescreve fisicamente os conteúdos na nova ordem
    size_t offset = 0;
    for (int i = 0; i < qtd_membros; i++) 
    {
        // Pega o offset original do membro[i]
        long offset_antigo = -1;
        int tamanho_comp = membros[i].tamanho_comp;

        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[i].nome, membros_originais[j].nome) == 0) 
            {
                offset_antigo = membros_originais[j].offset;
                break;
            }
        }

        if (offset_antigo == -1) 
        {
            printf("Erro interno: offset original não encontrado para '%s'\n", membros[i].nome);
            free(buffer);
            fclose(f);
            return 1;
        }

        // Lê do offset antigo
        if (fseek(f, offset_antigo, SEEK_SET) != 0 || fread(buffer, 1, (size_t)tamanho_comp, f) != (size_t)tamanho_comp) 
        {
            perror("Erro ao ler conteúdo original");
            free(buffer);
            fclose(f);
            return 1;
        }

        // Atualiza offset e ordem
        membros[i].offset = (long)offset;
        membros[i].ordem = i + 1;

        // Escreve no novo offset
        if (fseek(f, membros[i].offset, SEEK_SET) != 0 || fwrite(buffer, 1, (size_t)tamanho_comp, f) != (size_t)tamanho_comp) 
        {
            perror("Erro ao gravar conteúdo reorganizado");
            free(buffer);
            fclose(f);
            return 1;
        }

        offset += (size_t)tamanho_comp;
    }

    // Atualiza diretório
    if (fseek(f, 0, SEEK_END) != 0 || fwrite(membros, sizeof(Membro), qtd_membros, f) != (size_t)qtd_membros || fwrite(&qtd_membros, sizeof(int), 1, f) != 1) 
    {
        perror("Erro ao atualizar diretório");
        free(buffer);
        fclose(f);
        return 1;
    }

    free(buffer);
    fclose(f);
    printf("Membro '%s' movido com sucesso para após '%s'.\n", mover, target);
    return 0;
}


//============================================================================================================================



// Função que cria um novo arquivo derivado
int z_option(char *arquivo, int argc, char *argv[]) 
{
    // Abre o arquivo original em modo leitura binária
    FILE *orig = fopen(arquivo, "rb");
    if (!orig) 
    {
        printf("Erro: não foi possível abrir o arquivo '%s'\n", arquivo);
        return 1;
    }

    // Lê o diretório de membros do arquivo original
    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(orig, membros); 

    int qtd_solicitados = argc - 3;
    if (qtd_solicitados <= 0) 
    {
        printf("Erro: nenhum membro especificado para derivação.\n");
        fclose(orig);
        return 1;
    }

    Membro selecionados[MAX_MEMBROS]; 
    int encontrados = 0; 

    // Loop para processar cada membro solicitado na linha de comando
    for (int j = 3; j < argc; j++) 
    {
        int achou = 0;
        
        // Procura o membro na lista de membros do arquivo original
        for (int i = 0; i < qtd_membros; i++) 
        {
            if (strcmp(argv[j], membros[i].nome) == 0) 
            {
                selecionados[encontrados++] = membros[i];
                achou = 1;
                break;
            }
        }
        
        // Se o membro não foi encontrado, encerra
        if (!achou) 
        {
            printf("Erro: membro '%s' não encontrado no arquivo.\n", argv[j]);
            fclose(orig);
            return 1;
        }
    }

    // Cria o nome do arquivo derivado
    char nome_derivado[256];
    snprintf(nome_derivado, sizeof(nome_derivado), "%s_z", arquivo);

    // Abre o arquivo derivado em modo escrita binária
    FILE *derivado = fopen(nome_derivado, "wb");
    if (!derivado) 
    {
        printf("Erro: não foi possível criar o arquivo '%s'\n", nome_derivado);
        fclose(orig);
        return 1;
    }

    // Processa cada membro selecionado para copiar para o novo arquivo
    for (int i = 0; i < encontrados; i++) 
    {
        // Aloca memória para o buffer que armazenará o conteúdo do membro
        unsigned char *buffer = malloc(selecionados[i].tamanho_comp);
        if (!buffer) 
        {
            printf("Erro: falha ao alocar memória.\n");
            fclose(orig);
            fclose(derivado);
            return 1;
        }

        // Posiciona o ponteiro no arquivo original no início do membro
        fseek(orig, selecionados[i].offset, SEEK_SET);
        
        // Lê o conteúdo do membro no arquivo original
        size_t lidos = fread(buffer, 1, selecionados[i].tamanho_comp, orig);
        if (lidos != (size_t)selecionados[i].tamanho_comp) 
        {
            printf("Erro ao ler dados do membro '%s'\n", selecionados[i].nome);
            free(buffer);
            fclose(orig);
            fclose(derivado);
            return 1;
        }

        // Atualiza o offset do membro para a posição atual no novo arquivo
        selecionados[i].offset = ftell(derivado);
        
        // Escreve o conteúdo do membro no arquivo derivado
        fwrite(buffer, 1, selecionados[i].tamanho_comp, derivado);
        free(buffer);
    }

    // Atualiza a ordem dos membros no novo arquivo
    for (int i = 0; i < encontrados; i++)
        selecionados[i].ordem = i + 1;

    fwrite(selecionados, sizeof(Membro), encontrados, derivado);
    fwrite(&encontrados, sizeof(int), 1, derivado);

    // Fecha os arquivos
    fclose(orig);
    fclose(derivado);
    
    // Retorna sucesso
    return 0;
}
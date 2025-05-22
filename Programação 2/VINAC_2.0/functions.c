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
    Membro membros_existentes[MAX_MEMBROS];
    int qtd_existentes = 0;
    char *dados_antigos[MAX_MEMBROS] = {NULL}; // Para armazenar dados dos membros não substituídos

    // 1. Ler o archive existente (se existir)
    FILE *old_archive = fopen(arquivo, "rb");
    if (old_archive) 
    {
        fseek(old_archive, -sizeof(int), SEEK_END);
        fread(&qtd_existentes, sizeof(int), 1, old_archive);
        
        long membros_offset = -(sizeof(int) + qtd_existentes * sizeof(Membro));
        fseek(old_archive, membros_offset, SEEK_END);
        fread(membros_existentes, sizeof(Membro), qtd_existentes, old_archive);

        // Ler os dados de todos os membros existentes
        for (int i = 0; i < qtd_existentes; i++) {
            dados_antigos[i] = malloc(membros_existentes[i].tamanho_original);
            if (dados_antigos[i]) {
                fseek(old_archive, membros_existentes[i].offset, SEEK_SET);
                fread(dados_antigos[i], 1, membros_existentes[i].tamanho_original, old_archive);
            }
        }
        fclose(old_archive);
    }

    // 2. Criar novo archive
    FILE *new_archive = fopen(arquivo, "wb");
    if (!new_archive) 
    {
        printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
        for (int i = 0; i < qtd_existentes; i++) free(dados_antigos[i]);
        return 1;
    }

    Membro membros_finais[MAX_MEMBROS];
    int qtd_finais = 0;
    long current_offset = 0;

    // 3. Processar membros existentes
    for (int i = 0; i < qtd_existentes; i++) 
    {
        int substituido = 0;

        // Verificar se deve ser substituído
        for (int j = 3; j < argc; j++) 
        {
            if (strcmp(membros_existentes[i].nome, argv[j]) == 0) 
            {
                printf("Substituindo membro '%s'...\n", argv[j]);
                FILE *f = fopen(argv[j], "rb");
                if (!f) 
                {
                    printf("Erro ao abrir '%s'. Mantendo versão antiga.\n", argv[j]);
                    break;
                }

                // Criar novo membro
                Membro m = criar_membro(argv[j], qtd_finais + 1);
                m.offset = current_offset;
                m.comprimido = 0;

                // Ler e escrever dados
                fseek(f, 0, SEEK_END);
                m.tamanho_original = ftell(f);
                rewind(f);

                char *buffer = malloc(m.tamanho_original);
                if (buffer) {
                    fread(buffer, 1, m.tamanho_original, f);
                    fwrite(buffer, 1, m.tamanho_original, new_archive);
                    free(buffer);
                    current_offset += m.tamanho_original;
                } else {
                    printf("Erro de alocação para '%s'\n", argv[j]);
                }

                fclose(f);
                membros_finais[qtd_finais++] = m;
                substituido = 1;
                break;
            }
        }

        // Se não foi substituído, copiar do archive antigo
        if (!substituido && dados_antigos[i]) 
        {
            Membro m = membros_existentes[i];
            m.offset = current_offset;
            m.ordem = qtd_finais + 1;

            fwrite(dados_antigos[i], 1, m.tamanho_original, new_archive);
            current_offset += m.tamanho_original;
            membros_finais[qtd_finais++] = m;
        }
    }

    // 4. Adicionar novos membros
    for (int j = 3; j < argc; j++) 
    {
        int ja_existe = 0;
        for (int i = 0; i < qtd_finais; i++) {
            if (strcmp(membros_finais[i].nome, argv[j]) == 0) {
                ja_existe = 1;
                break;
            }
        }

        if (!ja_existe) {
            FILE *f = fopen(argv[j], "rb");
            if (f) {
                Membro m = criar_membro(argv[j], qtd_finais + 1);
                m.offset = current_offset;
                m.comprimido = 0;

                fseek(f, 0, SEEK_END);
                m.tamanho_original = ftell(f);
                rewind(f);

                char *buffer = malloc(m.tamanho_original);
                if (buffer) {
                    fread(buffer, 1, m.tamanho_original, f);
                    fwrite(buffer, 1, m.tamanho_original, new_archive);
                    free(buffer);
                    current_offset += m.tamanho_original;
                    membros_finais[qtd_finais++] = m;
                }
                fclose(f);
            }
        }
    }

    // 5. Escrever metadados no final
    fwrite(membros_finais, sizeof(Membro), qtd_finais, new_archive);
    fwrite(&qtd_finais, sizeof(int), 1, new_archive);

    // 6. Liberar memória e fechar arquivos
    for (int i = 0; i < qtd_existentes; i++) free(dados_antigos[i]);
    fclose(new_archive);

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
    // Tenta abrir o archive em modo leitura/escrita binária
    FILE *archive = fopen(arquivo, "r+b");
    if (!archive) 
    {
        // Se não existir, cria um novo archive
        archive = fopen(arquivo, "w+b");
        if (!archive) 
        {
            printf("Erro: não foi possível criar o arquivo de archive '%s'\n", arquivo);
            return 1;
        }
    }

    // Array para armazenar informações dos membros (arquivos contidos no archive)
    Membro membros[MAX_MEMBROS] = {0};  
    int qtd_membros = 0;
    long file_size = 0;

    // Verifica se o arquivo já contém dados
    if (fseek(archive, 0, SEEK_END) == 0) 
    {
        // Obtém o tamanho atual do archive
        file_size = ftell(archive);
        rewind(archive); // Volta para o início

        // Se o archive não estiver vazio, lê o diretório existente
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

    // Posiciona o ponteiro no final do archive para novas inserções
    if (fseek(archive, 0, SEEK_END) != 0) 
    {
        printf("Erro ao posicionar ponteiro no final do arquivo.\n");
        fclose(archive);
        return 1;
    }

    // Processa cada arquivo passado como argumento (a partir do 3º)
    for (int i = 3; i < argc; i++) 
    {
        const char *nome_membro = argv[i];
        
        // Abre o arquivo a ser inserido
        FILE *f = fopen(nome_membro, "rb");
        if (!f) 
        {
            printf("Erro: não foi possível abrir '%s'. Pulando...\n", nome_membro);
            continue;
        }

        // Calcula tamanho do arquivo
        if (fseek(f, 0, SEEK_END) != 0) 
        {
            printf("Erro ao buscar fim de '%s'. Pulando...\n", nome_membro);
            fclose(f);
            continue;
        }

        long tamanho_original = ftell(f);
        rewind(f);

        if (tamanho_original <= 0) 
        {
            printf("Arquivo '%s' vazio ou inválido. Pulando...\n", nome_membro);
            fclose(f);
            continue;
        }

        // Lê todo o conteúdo do arquivo para memória
        char *conteudo_original = malloc(tamanho_original);
        if (!conteudo_original) 
        {
            printf("Erro ao alocar memória para '%s'. Pulando...\n", nome_membro);
            fclose(f);
            continue;
        }

        if (fread(conteudo_original, 1, tamanho_original, f) != (size_t)tamanho_original) 
        {
            printf("Erro ao ler '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            fclose(f);
            continue;
        }
        fclose(f);

        // Tenta comprimir o conteúdo usando LZ
        char *conteudo_comp = malloc(tamanho_original);
        if (!conteudo_comp) 
        {
            printf("Erro ao alocar memória para compressão de '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            continue;
        }

        int tamanho_comp = LZ_Compress((unsigned char *)conteudo_original, (unsigned char *)conteudo_comp, tamanho_original);
        
        // Decide se usa o conteúdo original ou comprimido (baseado na eficiência da compressão)
        int usar_original = (tamanho_comp <= 0 || tamanho_comp >= tamanho_original);
        char *dados_finais = usar_original ? conteudo_original : conteudo_comp;
        int tamanho_final = usar_original ? tamanho_original : tamanho_comp;

        if (usar_original)
            printf("Aviso: compressão de '%s' ineficiente. Armazenando original.\n", nome_membro);

        // Verifica se o arquivo já existe no archive
        int idx_existente = -1;
        for (int j = 0; j < qtd_membros; j++) 
        {
            if (strcmp(membros[j].nome, nome_membro) == 0) 
            {
                idx_existente = j;
                break;
            }
        }

        // Obtém a posição atual no archive (onde os dados serão escritos)
        long offset = ftell(archive);
        if (offset < 0) 
        {
            printf("Erro ao obter offset para '%s'. Pulando...\n", nome_membro);
            free(conteudo_original);
            free(conteudo_comp);
            continue;
        }

        // Escreve os dados (originais ou comprimidos) no archive
        if (fwrite(dados_finais, 1, tamanho_final, archive) != (size_t)tamanho_final) 
        {
            printf("Erro ao escrever '%s' no archive. Pulando...\n", nome_membro);
            free(conteudo_original);
            free(conteudo_comp);
            continue;
        }

        if (idx_existente >= 0) 
        {
            // Atualiza membro existente no diretório
            membros[idx_existente].offset = offset;
            membros[idx_existente].tamanho_original = tamanho_original;
            membros[idx_existente].tamanho_comp = tamanho_final;
            membros[idx_existente].modificado_em = time(NULL);
            membros[idx_existente].comprimido = !usar_original;
            printf("Membro '%s' atualizado.\n", nome_membro);
        }
        else 
        {
            // Adiciona novo membro ao diretório
            if (qtd_membros >= MAX_MEMBROS) 
            {
                printf("Erro: número máximo de membros excedido. Ignorando '%s'.\n", nome_membro);
                free(conteudo_original);
                free(conteudo_comp);
                continue;
            }

            Membro novo = criar_membro(nome_membro, qtd_membros + 1);
            novo.offset = offset;
            novo.tamanho_original = tamanho_original;
            novo.tamanho_comp = tamanho_final;
            novo.modificado_em = time(NULL);
            novo.comprimido = !usar_original;
            membros[qtd_membros++] = novo;
        }

        free(conteudo_original);
        free(conteudo_comp);
    }

    // Recalcula a ordem/número dos membros
    for (int i = 0; i < qtd_membros; i++) 
        membros[i].ordem = i + 1;

    // Escreve o diretório atualizado no final do archive
    long inicio_dir = ftell(archive);
    if (inicio_dir < 0) 
    {
        printf("Erro ao obter posição do diretório.\n");
        fclose(archive);
        return 1;
    }

    // Escreve informações de cada membro
    for (int i = 0; i < qtd_membros; i++) 
        escrever_membro(archive, &membros[i]);

    // Escreve a quantidade total de membros
    if (fwrite(&qtd_membros, sizeof(int), 1, archive) != 1) 
    {
        printf("Erro ao escrever número de membros.\n");
        fclose(archive);
        return 1;
    }

    // Garante que todos os dados são escritos no disco
    fflush(archive);
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
    // Abre o arquivo archive em modo leitura binária
    FILE *archive = fopen(arquivo, "rb");
    if (!archive) 
    {
        printf("Erro: não foi possível abrir '%s'\n", arquivo);
        return 1;
    }

    // 2. LEITURA DO DIRETÓRIO
    // Lê a lista de membros (arquivos contidos) no archive
    Membro membros[MAX_MEMBROS];
    int qtd_membros = ler_diretorio(archive, membros);

    // 3. VERIFICAÇÃO DE ARGUMENTOS
    // Determina se deve extrair todos os membros (quando não há arquivos específicos)
    int extrair_todos = (argc <= 3);

    // 4. PREPARAÇÃO DO BUFFER
    // Encontra o maior tamanho entre os membros para alocação de buffer único
    long maior_tam = 0;
    for (int i = 0; i < qtd_membros; i++)
    {
        if (membros[i].tamanho_comp > maior_tam)
            maior_tam = membros[i].tamanho_comp;
    }

    // Aloca buffer com tamanho do maior membro encontrado
    unsigned char *buffer = malloc(maior_tam);
    if (!buffer) 
    {
        printf("Erro ao alocar memória\n");
        fclose(archive);
        return 1;
    }

    // 5. PROCESSAMENTO DOS MEMBROS
    // Itera por todos os membros do archive
    for (int i = 0; i < qtd_membros; i++) 
    {
        // 5.1 VERIFICA SE DEVE EXTRAIR ESTE MEMBRO
        int deve_extrair = extrair_todos; // Extrai todos se não houver argumentos

        // Se houver arquivos específicos, verifica se este membro está na lista
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

        // 5.2 EXTRAÇÃO DO MEMBRO
        if (deve_extrair) 
        {
            // Posiciona o ponteiro no início dos dados do membro
            fseek(archive, membros[i].offset, SEEK_SET);

            // Lê os dados compactados/armazenados para o buffer
            fread(buffer, 1, membros[i].tamanho_comp, archive);

            // Cria o arquivo de saída com o nome original do membro
            FILE *f_out = fopen(membros[i].nome, "wb");
            if (!f_out) 
            {
                printf("Erro ao criar '%s'. Pulando...\n", membros[i].nome);
                continue;
            }

            // 5.3 TRATAMENTO DE DADOS COMPACTADOS
            if (membros[i].comprimido) 
            {
                // Aloca buffer temporário para os dados descomprimidos
                unsigned char *saida = malloc(membros[i].tamanho_original);
                if (!saida) 
                {
                    printf("Erro ao alocar memória para descompressão\n");
                    fclose(f_out);
                    continue;
                }

                // Descomprime os dados usando o algoritmo LZ
                LZ_Uncompress(buffer, saida, membros[i].tamanho_comp);
                
                // Escreve os dados descomprimidos no arquivo de saída
                fwrite(saida, 1, membros[i].tamanho_original, f_out);
                
                // Libera o buffer de descompressão
                free(saida);
            } 
            else 
            {
                // 5.4 TRATAMENTO DE DADOS NÃO COMPACTADOS
                // Escreve diretamente os dados lidos no arquivo de saída
                fwrite(buffer, 1, membros[i].tamanho_original, f_out);
            }

            // Fecha o arquivo de saída
            fclose(f_out);
            
            // Comentado: poderia mostrar o progresso
            // printf("Extraído: %s\n", membros[i].nome);
        }
    }

    // 6. FINALIZAÇÃO
    // Libera o buffer principal
    free(buffer);
    
    // Fecha o arquivo archive
    fclose(archive);
    
    return 0; // Retorna sucesso
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

    if (idx_mover < nova_pos) {
        for (int i = idx_mover; i < nova_pos - 1; i++)
            membros[i] = membros[i + 1];
        membros[nova_pos - 1] = mover_membro;
    } else {
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
if (!buffer) {
    perror("malloc falhou");
    fclose(f);
    return 1;
}

// Reescreve fisicamente os conteúdos na nova ordem
size_t offset = 0;
for (int i = 0; i < qtd_membros; i++) {
    // Pega o offset original do membro[i]
    long offset_antigo = -1;
    int tamanho_comp = membros[i].tamanho_comp;

    for (int j = 0; j < qtd_membros; j++) {
        if (strcmp(membros[i].nome, membros_originais[j].nome) == 0) {
            offset_antigo = membros_originais[j].offset;
            break;
        }
    }

    if (offset_antigo == -1) {
        printf("Erro interno: offset original não encontrado para '%s'\n", membros[i].nome);
        free(buffer);
        fclose(f);
        return 1;
    }

    // Lê do offset antigo
    if (fseek(f, offset_antigo, SEEK_SET) != 0 ||
        fread(buffer, 1, (size_t)tamanho_comp, f) != (size_t)tamanho_comp) {
        perror("Erro ao ler conteúdo original");
        free(buffer);
        fclose(f);
        return 1;
    }

    // Atualiza offset e ordem
    membros[i].offset = (long)offset;
    membros[i].ordem = i + 1;

    // Escreve no novo offset
    if (fseek(f, membros[i].offset, SEEK_SET) != 0 ||
        fwrite(buffer, 1, (size_t)tamanho_comp, f) != (size_t)tamanho_comp) {
        perror("Erro ao gravar conteúdo reorganizado");
        free(buffer);
        fclose(f);
        return 1;
    }

    offset += (size_t)tamanho_comp;
}

    // Atualiza diretório
    if (fseek(f, 0, SEEK_END) != 0 ||
        fwrite(membros, sizeof(Membro), qtd_membros, f) != (size_t)qtd_membros ||
        fwrite(&qtd_membros, sizeof(int), 1, f) != 1) 
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
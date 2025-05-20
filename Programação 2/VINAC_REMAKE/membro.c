#include "membro.h"
#include "functions.h"


#define MAX_MEMBROS 1024

//==================================================================================================================================================


//  Cria um membro a partir de um arquivo do disco
Membro criar_membro(const char *nome_arquivo, int ordem) 
{
    Membro m;

    // Zera toda a struct para evitar dados não inicializados
    memset(&m, 0, sizeof(Membro));

    struct stat st;

    // Copia o nome do arquivo com segurança
    strncpy(m.nome, nome_arquivo, sizeof(m.nome) - 1);
    m.nome[sizeof(m.nome) - 1] = '\0';  // Garante '\0'

    // Obtém informações do arquivo
    if (stat(nome_arquivo, &st) == 0) 
    {
        m.tamanho_original = st.st_size;
        m.tamanho_comp = st.st_size;
        m.modificado_em = st.st_mtime;
    } 
    else 
    {
        perror("Erro ao acessar o arquivo");
        m.tamanho_original = m.tamanho_comp = 0;
        m.modificado_em = 0;
    }

    m.uid = obter_uid();
    m.ordem = ordem;
    m.offset = -1;

    return m;
}



//==================================================================================================================================================


//  Imprime os dados do membro
void imprimir_membro(const Membro *m) 
{
    char data[30];
    strftime(data, sizeof(data), "%Y-%m-%d %H:%M:%S", localtime(&m->modificado_em));

    printf("Nome: %s | UID: %d | Orig: %ld | Comp: %ld | Data: %s | Ordem: %d | Offset: %ld\n",
           m->nome, m->uid, m->tamanho_original, m->tamanho_comp, data, m->ordem, m->offset);
}


//==================================================================================================================================================


// Função para escrever o membro em um arquivo binário
void escrever_membro(FILE *f, const Membro *m) 
{
    fwrite(m, sizeof(Membro), 1, f);
}


//==================================================================================================================================================


//  Lê o diretório de membros do arquivo
int ler_diretorio(FILE *f, Membro membros[]) 
{
    long pos_atual = ftell(f);

    // Vai para o fim do arquivo para ler o início do diretório
    fseek(f, -sizeof(int), SEEK_END);

    int qtd_membros;
    fread(&qtd_membros, sizeof(int), 1, f);

    // Volta para o início do diretório
    fseek(f, -(sizeof(int) + qtd_membros * sizeof(Membro)), SEEK_END);

    fread(membros, sizeof(Membro), qtd_membros, f);

    // Retorna o ponteiro para onde estava antes
    fseek(f, pos_atual, SEEK_SET);

    return qtd_membros;
}


//==================================================================================================================================================


//  Carrega os membros já existentes do archive
int carregar_membros(const char *arquivo, Membro membros[]) 
{
    int qtd = 0;
    FILE *f = fopen(arquivo, "rb");
    if (f) 
    {
        qtd = ler_diretorio(f, membros);
        fclose(f);
    }
    return qtd;
}


//==================================================================================================================================================

// Salva o vetor de membros e a quantidade de membros do final do archive
void salvar_membros(FILE *archive, Membro membros[], int qtd) 
{
    fwrite(membros, sizeof(Membro), qtd, archive);
    fwrite(&qtd, sizeof(int), 1, archive);
}


//==================================================================================================================================================


// Função para copiar o conteúdo de um arquivo para outro com buffer
void copiar_conteudo(FILE *src, FILE *dst) 
{
    if (!src || !dst) return;

    char buffer[1024];
    size_t lidos;

    if (fseek(src, 0, SEEK_SET) != 0) 
    {
        perror("Erro ao reposicionar o ponteiro de leitura");
        return;
    }

    while ((lidos = fread(buffer, 1, sizeof(buffer), src)) > 0) 
    {
        size_t escritos = fwrite(buffer, 1, lidos, dst);
        if (escritos != lidos) 
        {
            perror("Erro ao escrever no arquivo de destino");
            break;
        }
    }
}


//==================================================================================================================================================


//  Regravar no novo arquivo archive os membros antigos que não devem ser substituídos
int regravar_membros(FILE *archive, Membro membros_existentes[], int qtd_existentes, char *argv[], int argc, Membro membros_finais[]) 
{
    if (!archive || !membros_existentes || !membros_finais || !argv) return 0;

    int qtd_finais = 0;

    for (int i = 0; i < qtd_existentes; i++) 
    {
        int substituir = 0;

        for (int j = 3; j < argc; j++) 
        {
            if (strcmp(membros_existentes[i].nome, argv[j]) == 0) 
            {
                printf("Membro [%s] já existe. Substituindo!\n", argv[j]);
                substituir = 1;
                break;
            }
        }

        if (!substituir) 
        {
            FILE *f = fopen(membros_existentes[i].nome, "rb");
            if (!f) 
            {
                fprintf(stderr, "Aviso: não foi possível reabrir '%s'. Pulando...\n", membros_existentes[i].nome);
                continue;
            }

            Membro m = membros_existentes[i];
            m.offset = ftell(archive);
            copiar_conteudo(f, archive);
            fclose(f);

            membros_finais[qtd_finais++] = m;
        }
    }

    return qtd_finais;
}


//==================================================================================================================================================


// Adiciona novos membros ao archive
int adicionar_membros(FILE *archive, char *argv[], int argc, int qtd_inicial, Membro membros_finais[]) 
{
    if (!archive || !argv || !membros_finais) return qtd_inicial;

    int qtd = qtd_inicial;

    for (int i = 3; i < argc; i++) 
    {
        const char *nome = argv[i];

        if (!nome) continue;

        FILE *f = fopen(nome, "rb");
        if (!f) 
        {
            fprintf(stderr, "Erro: não foi possível abrir '%s'. Pulando...\n", nome);
            continue;
        }

        Membro m = criar_membro(nome, 0);
        m.offset = ftell(archive);

        copiar_conteudo(f, archive);
        fclose(f);

        membros_finais[qtd++] = m;
    }

    return qtd;
}


//==================================================================================================================================================
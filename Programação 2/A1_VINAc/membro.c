#include "membro.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

//===================================================================================

Membro criar_membro(const char *nome_arquivo, int ordem) 
{
    Membro m;
    struct stat st;

    // Limpar o campo nome antes de copiar
    memset(m.nome, 0, sizeof(m.nome));  // Limpa para evitar lixo de memória

    // Copia o nome do arquivo, garantindo que não ultrapasse o tamanho máximo
    strncpy(m.nome, nome_arquivo, sizeof(m.nome) - 1);
    m.nome[sizeof(m.nome) - 1] = '\0';  // Garante que o nome termina com '\0'

    // Obtém informações sobre o arquivo
    if (stat(nome_arquivo, &st) == 0) 
    {
        m.tamanho_original = st.st_size;
        m.tamanho_comp = st.st_size;  // sem compressão por enquanto
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
    m.offset = -1;  // será atribuído ao salvar

    return m;
}

//===================================================================================

void imprimir_membro(const Membro *m) 
{
    char data[30];
    strftime(data, sizeof(data), "%Y-%m-%d %H:%M:%S", localtime(&m->modificado_em));

    printf("Nome: %s | UID: %d | Orig: %ld | Comp: %ld | Data: %s | Ordem: %d | Offset: %ld\n",
           m->nome, m->uid, m->tamanho_original, m->tamanho_comp, data, m->ordem, m->offset);
}

//===================================================================================

void escrever_membro(FILE *f, const Membro *m) 
{
    fwrite(m, sizeof(Membro), 1, f);
}

//===================================================================================

int ler_membro(FILE *f, Membro *m) 
{
    return fread(m, sizeof(Membro), 1, f) == 1;
}

//===================================================================================

void salvar_membro(FILE *archive, const char *nome_arquivo, int ordem) 
{
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) 
    {
        fprintf(stderr, "Erro: não foi possível abrir '%s'. Pulando...\n", nome_arquivo);
        return;
    }

    // Cria o membro com os metadados
    Membro m = criar_membro(nome_arquivo, ordem);
    m.offset = ftell(archive) + sizeof(Membro);

    // Escreve o cabeçalho do membro no archive
    escrever_membro(archive, &m);

    // Copia o conteúdo do arquivo para o archive
    char buffer[1024];
    size_t lidos;
    while ((lidos = fread(buffer, 1, sizeof(buffer), f)) > 0) 
    {
        fwrite(buffer, 1, lidos, archive);
    }

    fclose(f);
    printf("Membro '%s' salvo com sucesso! (Offset: %ld)\n", m.nome, m.offset);
}

//===================================================================================
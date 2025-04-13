#include "membro.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>



Membro criar_membro(const char *nome_arquivo, int ordem) 
{
    Membro m;
    struct stat st;

    strncpy(m.nome, nome_arquivo, sizeof(m.nome));
    m.nome[sizeof(m.nome) - 1] = '\0';

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
    m.offset = -1;  // será atribuído depois

    return m;
}

void imprimir_membro(const Membro *m) 
{
    char data[30];
    strftime(data, sizeof(data), "%Y-%m-%d %H:%M:%S", localtime(&m->modificado_em));

    printf("Nome: %s | UID: %d | Orig: %ld | Comp: %ld | Data: %s | Ordem: %d | Offset: %ld\n",
           m->nome, m->uid, m->tamanho_original, m->tamanho_comp, data, m->ordem, m->offset);
}

void escrever_membro(FILE *f, const Membro *m) 
{
    fwrite(m, sizeof(Membro), 1, f);
}

int ler_membro(FILE *f, Membro *m) 
{
    return fread(m, sizeof(Membro), 1, f);
}
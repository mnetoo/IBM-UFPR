#include "membro.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

//===================================================================================


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



//===================================================================================


//  Imprime os dados do membro
void imprimir_membro(const Membro *m) 
{
    char data[30];
    strftime(data, sizeof(data), "%Y-%m-%d %H:%M:%S", localtime(&m->modificado_em));

    printf("Nome: %s | UID: %d | Orig: %ld | Comp: %ld | Data: %s | Ordem: %d | Offset: %ld\n",
           m->nome, m->uid, m->tamanho_original, m->tamanho_comp, data, m->ordem, m->offset);
}


//===================================================================================


// Função para escrever o membro em um arquivo binário
void escrever_membro(FILE *f, const Membro *m) 
{
    fwrite(m, sizeof(Membro), 1, f);
}


//===================================================================================


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


//===================================================================================
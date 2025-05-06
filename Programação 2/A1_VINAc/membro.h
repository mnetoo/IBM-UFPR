#ifndef MEMBRO_H
#define MEMBRO_H

#include <time.h>
#include <stdio.h>

typedef struct 
{
    char nome[256];         // nome do arquivo (sem espaços)
    int uid;                // UID do criador
    long tamanho_original;  // tamanho antes da compressão
    long tamanho_comp;      // tamanho depois da compressão (igual ao original se não foi comprimido)
    time_t modificado_em;   // data/hora da última modificação
    int ordem;              // ordem no arquivo
    long offset;            // onde os dados começam no arquivo archive
} Membro;

// Cria um membro a partir de um arquivo do disco
Membro criar_membro(const char *nome_arquivo, int ordem);

// Imprime os dados do membro
void imprimir_membro(const Membro *m);

// Escreve membro em um arquivo binário
void escrever_membro(FILE *f, const Membro *m);

// Lê membro de um arquivo binário
int ler_membro(FILE *f, Membro *m);

void salvar_membro(FILE *archive, const char *nome_arquivo, int ordem);

int ler_diretorio(FILE *f, Membro membros[]);

#endif
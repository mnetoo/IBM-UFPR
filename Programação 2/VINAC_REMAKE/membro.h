#ifndef MEMBRO_H
#define MEMBRO_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "functions.h"
#include "lz.h"


//============================================================================================================================


//Estrutura de membro
typedef struct 
{
    char nome[256];         // nome do arquivo (sem espaços)
    int uid;                // UID do criador
    long tamanho_original;  // tamanho antes da compressão
    long tamanho_comp;      // tamanho depois da compressão (igual ao original se não foi comprimido)
    time_t modificado_em;   // data/hora da última modificação
    int ordem;              // ordem no arquivo
    long offset;            // onde os dados começam no arquivo archive
    int comprimido;         // 1 se comprimido, 0 se não
} Membro;


//============================================================================================================================

// Cria um membro a partir de um arquivo do disco
Membro criar_membro(const char *nome_arquivo, int ordem);

//============================================================================================================================

// Imprime os dados do membro
void imprimir_membro(const Membro *m);

//============================================================================================================================

// Escreve membro em um arquivo binário
void escrever_membro(FILE *f, const Membro *m);

//============================================================================================================================

// Lê membro de um arquivo binário
int ler_membro(FILE *f, Membro *m);

//============================================================================================================================

//  Lê o diretório de membros do arquivo
int ler_diretorio(FILE *f, Membro membros[]);

//============================================================================================================================


int carregar_membros(const char *arquivo, Membro membros[]);

//============================================================================================================================

//
void salvar_membros(FILE *archive, Membro membros[], int qtd);

//============================================================================================================================

//
void copiar_conteudo(FILE *src, FILE *dst);

//============================================================================================================================

//
int regravar_membros(FILE *archive, Membro membros_existentes[], int qtd_existentes, char *argv[], int argc, Membro membros_finais[]);

//============================================================================================================================

//
int adicionar_membros(FILE *archive, char *argv[], int argc, int qtd_inicial, Membro membros_finais[]); 

//============================================================================================================================

#endif
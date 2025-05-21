/*
    Arquivo de cabeçalho para protótipos das funções
    para o software Arquivador VINAc.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX_MEMBROS 1024

//===================================================================

//  Função para inserir/atualizar arquivos sem compressão em um archive
// Parâmetros:
// - arquivo: nome do arquivo archive
// - argc: contagem de argumentos da linha de comando
// - argv: array de argumentos da linha de comando
int p_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função para inserir/atualizar arquivos com compressão em um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos a inserir)
int i_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função para listar os membros do archive
int c_option(char *arquivo);

//===================================================================

// Função para remover arquivos de um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos a remover)
int r_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função para extrair arquivos de um archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos (argv[3..] contém os arquivos específicos a extrair)
int x_option(char *arquivo, int argc, char *argv[]);

//===================================================================


// Função para mover/reordenar membros dentro do archive
// Parâmetros:
// - arquivo: nome do archive
// - argc: contagem de argumentos
// - argv: vetor de argumentos
//   [3]: target (membro de referência ou "NULL" para início)
//   [4]: mover (membro a ser movido)
int m_option(char *arquivo, int argc, char *argv[]);

//===================================================================


//  Função que obtém o UID do usuário atual
int obter_uid();

#endif
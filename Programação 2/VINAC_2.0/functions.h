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
#include <sys/stat.h> // Para stat (informações do arquivo)
#include <unistd.h>   // Para getuid (embora usemos st_uid para dono do arquivo)
#include <errno.h>    // Para errno (diagnóstico de erros de remove/rename)

//===================================================================

//  Função para inserir sem compressão
int p_option(char *arquivo, int argc, char *argv[]);

//===================================================================

//  Função para inserir com compressão
int i_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função para listar os membros do archive
int c_option(char *arquivo);

//===================================================================

// Função que move o membro indicado na linha de comando
int m_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função que extrai os membros indicados de archive
int x_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função que remove os membros indicados de archive
int r_option(char *arquivo, int argc, char *argv[]);

//===================================================================

//  Funções auxiliares

time_t obter_data_modificacao(const char *nome_arquivo);

int obter_uid();

//===================================================================


#endif
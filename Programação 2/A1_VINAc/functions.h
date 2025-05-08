#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <time.h>







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
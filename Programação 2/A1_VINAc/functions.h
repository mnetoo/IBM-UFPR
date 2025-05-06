#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <time.h>







//===================================================================

//  Função para inserir sem compressão
int ip_option(char *arquivo, int argc, char *argv[]);

//===================================================================

//  Função para inserir com compressão
int ic_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função para listar os membros do archive
int c_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função que processa a opção "-m"
int m_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função que processa a opção "-x"
int x_option(char *arquivo, int argc, char *argv[]);

//===================================================================

// Função que processa a opção "-r"
int r_option(char *arquivo, int argc, char *argv[]);

//===================================================================

time_t obter_data_modificacao(const char *nome_arquivo);

//===================================================================

int obter_uid();

//===================================================================


#endif
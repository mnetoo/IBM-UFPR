#ifndef FILA_JORNAL
#define FILA_JORNAL


#include <stdio.h>
#include <stdlib.h>

//  STRUCTS

typedef struct noticia
{
    char titulo[33];
    char texto[513];
    char idade;
    struct noticia *prox;
} noticia;


//  Sentinela
typedef struct fila_jornal
{
    noticia *inicio;
    noticia *final;
} fila_jornal;

//=====================================================================================================



//  FUNÇÕES





noticia* criar_noticia();

int inserir_noticia(noticia *nova, fila_jornal *fila);

noticia* remover_noticia(fila_jornal *fila);

void atualizar_fila(fila_jornal *fila);

void destruir_fila(fila_jornal *fila);







#endif
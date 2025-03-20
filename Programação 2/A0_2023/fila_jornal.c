#include <stdio.h>
#include <stdlib.h>
#include "fila_jornal.h"



void requisitar_noticia(char *titulo, char *texto)
{
    getchar();

    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);

    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}




//  Cria uma nova notícia
noticia* criar_noticia()
{
    //  Aloca nova notícia
    noticia *nova = (noticia*) malloc(sizeof(noticia));

    //  Se não alocado retorna erro
    if (!nova)
        return NULL;

    //  Lê parâmetros da notícia
    requisitar_noticia(nova->titulo, nova->texto);
    
    //  Inicializa
    nova->idade = 0;
    nova->prox = NULL;

    return nova;
}




int inserir_noticia(noticia *nova, fila_jornal *fila)
{
    if(!nova )
        return -1;
    if(!fila)
    return -2;

    //  Se não estiver vazia, atualiza o final 
    if(fila->final)
    {
        fila->final->prox = nova;
        nova->prox = NULL;
        fila->final = nova;
    }
    //  Se tiver vazia, atualiza o inicio e fim porque é o primeiro elemento
    else
    {
        fila->inicio = nova;
        fila->final = nova;
    }

    return 0;
}




noticia* remover_noticia(fila_jornal *fila)
{
    if(!fila  || !fila->inicio)
        return NULL;


    noticia *retorno = fila->inicio;
    fila->inicio = retorno->prox;

    if(!retorno->prox)
        fila->final = NULL;

    return retorno;
}





void atualizar_fila(fila_jornal *fila)
{
    if(!fila)
        return;

    for(noticia *iterador = fila->inicio; (iterador && iterador->idade == 3); iterador = fila->inicio)
        free(remover_noticia(fila));
            
    for(noticia *iterador = fila->inicio; iterador; iterador->idade++, iterador = iterador->prox);
}





void destruir_fila(fila_jornal *fila)
{
    while(fila->inicio)
        free(remover_noticia(fila));

    free(fila);
}
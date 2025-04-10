#include <stdlib.h>
#include <string.h>

#include "pedido.h"

pedido* criar_pedido(char* musica, float valor){
	pedido *novo;

	novo = (pedido*) malloc (sizeof(pedido));
	novo->musica = strdup(musica);
	novo->valor = valor;
	novo->proximo = NULL;
	novo->anterior = NULL;
	
	return novo;
}

void destruir_pedido(pedido* elemento){

	free(elemento->musica);
	free(elemento);
}
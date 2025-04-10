#ifndef __PEDIDO__
#define __PEDIDO__

typedef struct pedido{
	char* musica;
	float valor;

	struct pedido *proximo;
	struct pedido *anterior;
} pedido;

pedido* criar_pedido(char* musica, float valor);
void destruir_pedido(pedido* elemento);

#endif
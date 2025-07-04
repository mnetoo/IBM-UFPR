#include <stdlib.h>
#include <stdio.h>
#include "jukefila.h"

void lance_jukebox(jukefila* fila){
	char musica[51];
	float valor = 0;

	printf("Digite o nome da música: ");
	fgetc(stdin);
	scanf("%50[^\n]", musica);
	do{
		printf("Digite o valor da música (min. R$1): R$");
		scanf("%f", &valor);
	} while(valor < 1);

	inserir_jukefila(criar_pedido(musica, valor), fila);
}


void toca_jukebox(jukefila *fila){

	pedido* proximo = consumir_jukefila(fila);
	if (proximo != NULL){
		printf("Tocou a música %s com o lance %f (%u pedidos na fila)\n", proximo->musica, proximo->valor, contar_jukefila(fila));
		destruir_pedido(proximo);
	} else {
		printf("Não há pedidos de música para serem atendidos\n");
	}
}

int main(void){
	int opcao;
	jukefila *fila;

	fila = criar_jukefila();
	printf("================ JUKEBOX MERCENÁRIA ================\n");
	while(1){
		printf("1 - Fazer pedido\n");
		printf("2 - Atender pedido\n");
		printf("3 - Sair\n");
		printf("Digite a opção: ");
		scanf("%d", &opcao);

		if (opcao == 1)
			lance_jukebox(fila);
		else if (opcao == 2)
			toca_jukebox(fila);
		else if (opcao == 3)
			break;
		else
			continue;
	}

	destruir_jukefila(fila);
	return 0;
}
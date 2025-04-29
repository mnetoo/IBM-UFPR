/*
    Disciplina: Algoritmos e Estrutura de Dados III.
    Professor: Prof. Dr. Eduardo Cunha de Almeida.
    Aluno: Marcus Sebastião Adriano Rocha Neto.
    GRR: 20240710.
    Curso: Informática Biomédica.
    Descrição: Trabalho 1, implementação Árvore Rubro Negra.
*/

#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

int main() 
{
	char opcao;
	int valor;

	struct arvore* arvore = cria_arvore();
	
	while (scanf(" %c %d", &opcao, &valor) == 2) 
	{
		if (opcao == 'i')
		{
			struct nodo *z = cria_nodo(NILL, valor);
			inserir(arvore, z);
			ajustar_nivel(arvore->raiz, 0);
		}

		else if(opcao == 'r')
		{
			struct nodo *z = busca_no(arvore->raiz, valor);
			if (z != NILL) 
			{
				remover(arvore, z);
				ajustar_nivel(arvore->raiz, 0);
			} 
			else
				printf("Nó %d não encontrado para remoção!\n", valor);
		}
	}

	imprimir(arvore->raiz);

	// Destrói a árvore (libera nós e estrutura)
    destruir_arvore(arvore);
}
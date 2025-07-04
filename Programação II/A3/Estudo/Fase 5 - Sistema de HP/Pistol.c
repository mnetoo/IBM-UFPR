#include <stdlib.h>
#include "Pistol.h"

pistol* pistol_create(){																				//Implementação da função "pistol_create"

	pistol *new_pistol = (pistol*) malloc(sizeof(pistol));												//Aloca a memória na heap para uma instância de pistola
	if (!new_pistol) return NULL;																		//Verifica o sucesso da alocação de memória; retorna NULL em caso de falha
	new_pistol->timer = 0;																				//Inicializa o relógio de disparos em zero (pronto para atirar)
	new_pistol->shots = NULL;																			//Inicializa a lista de disparos com NULL; ou seja, sem disparos
	return new_pistol;																					//Retorna a nova instância de pistola
}

bullet* pistol_shot(unsigned short x, unsigned short y, unsigned char trajectory, pistol *gun){			//Implementação da função "pistol_shot"
	
	bullet *new_bullet = bullet_create(x, y, trajectory, gun->shots);									//Cria uma nova instância de projétil a ser disparado
	if (!new_bullet) return NULL;																		//Verifica o sucesso da alocação de memória; retorna NULL em caso de falha
	return new_bullet;																					//Retorna uma nova instância de projétil
}

void pistol_destroy(pistol *element){																	//Implementação da função "pistol_destroy"

	bullet *sentinel;																					//Sentinela para a remoção de projéteis ativos
	for (bullet *index = element->shots; index != NULL; index = sentinel){								//Para cada projétil na lista de disparos
		sentinel = (bullet*) index->next;																//Armazena o próximo projétil
		bullet_destroy(index);																			//Chama o destrutor do projétil atual
	}
	free(element);																						//Libera a memória da instância de pistola
}
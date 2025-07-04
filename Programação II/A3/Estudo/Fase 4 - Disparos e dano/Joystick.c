#include <stdlib.h>
#include "Joystick.h"

joystick* joystick_create(){														//Implementação da função "joystick_create"

	joystick *element = (joystick*) malloc (sizeof(joystick));						//Aloca memória na heap para um novo controle
	if (!element) return NULL;														//Se a alocação não deu certo, retorna erro
	element->right = 0;																//Insere o estado de desligado para o botão de movimentação à esquerda
	element->left = 0;																//Insere o estado de desligado para o botão de movimentação à direita
	element->up = 0;																//Insere o estado de desligado para o botão de movimentação para cima
	element->down = 0;																//Insere o estado de desligado para o botão de movimentação para baixo
	element->fire = 0;																//Insere o estado de desligado para o botão de disparo (!)
	return element;																	//Retorna o novo controle
}

void joystick_destroy(joystick *element){ free(element);}							//Implementação da função "joystick_destroy"; libera a memória do elemento na heap

void joystick_left(joystick *element){ element->left = element->left ^ 1;}			//Implementação da função "joystick_left"; muda o estado do botão

void joystick_right(joystick *element){ element->right = element->right ^ 1;}		//Implementação da função "joystick_right"; muda o estado do botão

void joystick_up(joystick *element){ element->up = element->up ^ 1;}				//Implementação da função "joystick_up"; muda o estado do botão

void joystick_down(joystick *element){ element->down = element->down ^ 1;}			//Implementação da função "joystick_down"; muda o estado do botão

void joystick_fire(joystick *element){ element->fire = element->fire ^ 1;}			//Implementação da função "joystick_fire"; muda o estado do botão (!)
#include <stdlib.h>
#include "Square.h"

square* square_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){			//Implementação da função "square_create"

	if ((x - side/2 < 0) || (x + side/2 > max_x) || (y - side/2 < 0) || (y + side/2 > max_y)) return NULL;												//Verifica se a posição inicial é válida; caso não seja, retorna NULL
	if (face > 3) return NULL;																															//Verifica se a face principal do quadrado é válida

	square *new_square = (square*) malloc(sizeof(square));																								//Aloca memória na heap para um novo quadrado
	if (!new_square) return NULL;																														//Se a alocação não deu certo, retorna erro													
	new_square->side = side;																															//Insere o tamanho do lado de um quadrado
	new_square->face = face;																															//Insere a indicação da face principal do quadrado
	new_square->hp = 5;																																	//Insere o total de pontos de vida de um quadrado (!)
	new_square->x = x;																																	//Insere a posição inicial central de X
	new_square->y = y;																																	//Insere a posição inicial central de Y
	new_square->control = joystick_create();																											//Insere o elemento de controle do quadrado
	new_square->gun = pistol_create();																													//Insere o elemento de disparos do quadrado
	return new_square;																																	//Retorna o novo quadrado
}

void square_move(square *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									//Implementação da função "square_move"

	if (!trajectory){ if ((element->x - steps*SQUARE_STEP) - element->side/2 >= 0) element->x = element->x - steps*SQUARE_STEP;} 						//Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 1){ if ((element->x + steps*SQUARE_STEP) + element->side/2 <= max_x) element->x = element->x + steps*SQUARE_STEP;}			//Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 2){ if ((element->y - steps*SQUARE_STEP) - element->side/2 >= 0) element->y = element->y - steps*SQUARE_STEP;}				//Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
	else if (trajectory == 3){ if ((element->y + steps*SQUARE_STEP) + element->side/2 <= max_y) element->y = element->y + steps*SQUARE_STEP;}			//Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma
}

void square_shot(square *element){																														//Implementação da função "square_shot"
	bullet *shot;

	if (!element->face) shot = pistol_shot(element->x - element->side/2, element->y, element->face, element->gun);										//Quadrado atira para a esquerda
	else if (element->face == 1) shot = pistol_shot(element->x + element->side/2, element->y, element->face, element->gun);								//Quadrado atira para a direita
	if (shot) element->gun->shots = shot;
}

void square_destroy(square *element){																													//Implementação da função "square_destroy"
	
	pistol_destroy(element->gun);																														//Destrói o armemento do quadrado
	joystick_destroy(element->control);																													//Destrói o controle do quadrado
	free(element);																																		//Libera a memória do quadrado na heap
}
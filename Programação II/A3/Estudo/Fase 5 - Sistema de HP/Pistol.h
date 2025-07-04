#ifndef __PISTOL__ 																												//Guardas de inclusão
#define __PISTOL__																												//Guardas de inclusão

#include "Bullet.h"

#define PISTOL_COOLDOWN 10																										//Tamanho, em frames, do tempo entre um tiro e outro

typedef struct {																												//Definição da estrutura de uma pistola
	unsigned char timer;																										//Relógio de intervalo entre tiros
	bullet *shots;																												//Lista de balas ativas no campo disparadas pelas arma	
} pistol;																														//Definição do nome da estrutura

pistol* pistol_create();																										//Protótipo da função de criação de uma pistola
bullet* pistol_shot(unsigned short x, unsigned short y, unsigned char trajectory, pistol *gun);									//Protótipo da função de disparo de uma pistola
void pistol_destroy(pistol *element);																							//Protótipo da função de destruição de uma pistola

#endif																															//Guardas de inclusão
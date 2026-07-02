#ifndef EVENTOS
#define EVENTOS

#include "fprio.h"
#include "conjunto.h"
#include "lista.h"
#include "entidades.h"





// Função para gerar número aleatório em um intervalo
int aleat(int min, int max);

//  FUNÇÃO PARA CRIAR MUNDO - INICIALIZA HERÓIS, BASES, MISSÕES
struct mundo cria_mundo();

//  FUNÇÃO PARA DESTRUIR O MUNDO CRIADO
void destroi_mundo(struct mundo *mundo);

//  TIRA O HEROI DO CONJUNTO DE PRESENTES DA BASE 
//  RETORNA UMA BASE ALEATÓRIA
int sai (int tempo, struct mundo *mundo, int h, int b);

//  CALCULA O TPB E RETORNA O VALOR
int entra (int tempo, struct mundo *mundo, int h, int b);

//  FUNÇÃO QUE AVISA O ESTADO DE UMA BASE PARA O PORTEIRO
void avisa (int tempo, struct mundo mundo, int b);

//  FUNÇÃO PARA ADICIONAR O HEROI NA FILA DE ESPERA DA BASE
void espera (int tempo, struct mundo mundo, int h, int b);

//  FUNÇÃO QUE CALCULA DISTÂNCIA DO HERIO ATEÉ A OUTRA BASE E RETORNA A DURAÇÃO
int viaja (int tempo, struct mundo *mundo, int h, int base_destino);

//  DEFINE UMA BASE DE DESTINO ALEATÓRIA
int desiste (int tempo, struct mundo *mundo, int h, int b);

//  EVENTO CHEGA
//  HEROI (H) CHEGA NA BASE (B) NO TEMPO (T), (H) ANALISA O TAM_FILA E DECIDE SE ESPERA
int chega (int tempo, struct mundo mundo, int h, int b);

// FUNÇÃO EVENTO FIM
void fim (int tempo, struct mundo *mundo);

int compara (const void* a, const void* b) ;

//  Evento MORRE 
//  MARCA A MORTE DE UM HEROI, LIBERA A VAGA E AVISA O PORTEIRO DA BASE
void morre (int tempo, struct mundo *mundo, struct fprio_t *f ,int h, int b);

/* 
 * Cria um evento contendo os parâmetros informados.
 * Retorna um ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2);

/* 
 * Destroi um evento e retorna NULL.
 */ 
struct evento_t *destroi_evento (struct evento_t *e);

int missao (int tempo, int indice_missao, struct mundo *mundo);

void *fprio_retira(struct fprio_t *f, int *tipo, int *prio);




#endif
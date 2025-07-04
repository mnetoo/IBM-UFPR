//Compilação: gcc AggressiveSquares.c Square.c Joystick.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags) (!)

#include <allegro5/allegro5.h>																																											//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																																										//Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>																																								//Biblioteca de figuras básicas

#include "Square.h"

#include <stdio.h>																																														//Inclusão da biblioteca de quadrados

#define X_SCREEN 320																																													//Definição do tamanho da tela em pixels no eixo x
#define Y_SCREEN 320																																													//Definição do tamanho da tela em pixels no eixo y

unsigned char collision_2D(square *element_first, square *element_second){

	if ((((element_first->y+element_first->side/2 >= element_second->y-element_second->side/2) && (element_second->y-element_second->side/2 >= element_first->y-element_first->side/2)) || 	//			//Verifica se o primeiro elemento colidiu com o segundo no eixo X			
		((element_second->y+element_second->side/2 >= element_first->y-element_first->side/2) && (element_first->y-element_first->side/2 >= element_second->y-element_second->side/2))) && 	//			//Verifica se o segundo elemento colidiu com o primeiro no eixo X
		(((element_first->x+element_first->side/2 >= element_second->x-element_second->side/2) && (element_second->x-element_second->side/2 >= element_first->x-element_first->side/2)) || 	//			//Verifica se o primeiro elemento colidiu com o segundo no eixo Y
		((element_second->x+element_second->side/2 >= element_first->x-element_first->side/2) && (element_first->x-element_first->side/2 >= element_second->x-element_second->side/2)))) return 1;		//Verifica se o segundo elemento colidiu com o primeiro no eixo Y
	else return 0;
}

void update_position(square *player_1, square *player_2){																																				//Função de atualização das posições dos quadrados conforme os comandos do controle (!)
	
	if (player_1->control->left){																																										//Se o botão de movimentação para esquerda do controle do primeiro jogador está ativado... (!)
		square_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do primeiro jogador para a esquerda (!)
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 0, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	if (player_1->control->right){																																										//Se o botão de movimentação para direita do controle do primeir ojogador está ativado... (!)
		square_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do primeiro jogador para a direta (!)
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	if (player_1->control->up) {																																										//Se o botão de movimentação para cima do controle do primeiro jogador está ativado... (!)
		square_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do primeiro jogador para cima (!)
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 2, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	if (player_1->control->down){																																										//Se o botão de movimentação para baixo do controle do primeiro jogador está ativado... (!)
		square_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do primeiro jogador para a baixo (!)
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 3, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}

	if (player_2->control->left){																																										//Se o botão de movimentação para esquerda do controle do segundo jogador está ativado... (!)
		square_move(player_2, 1, 0, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do segundo jogador para a esquerda (!)
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 0, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	
	if (player_2->control->right){ 																																										//Se o botão de movimentação para direita do controle do segundo jogador está ativado... (!)
		square_move(player_2, 1, 1, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do segundo jogador para a direita (!)
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 1, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
	
	if (player_2->control->up){																																											//Se o botão de movimentação para cima do controle do segundo jogador está ativado... (!)
		square_move(player_2, 1, 2, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do segundo jogador para a cima (!)
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 2, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)			
	}
	if (player_2->control->down){																																										//Se o botão de movimentação para baixo do controle do segundo jogador está ativado... (!)
		square_move(player_2, 1, 3, X_SCREEN, Y_SCREEN);																																				//Move o quadrado do segundo jogador para a baixo (!)
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 3, X_SCREEN, Y_SCREEN);																											//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo (!)
	}
}

int main(){
	al_init();																																															//Faz a preparação de requisitos da biblioteca Allegro
	al_init_primitives_addon();																																											//Faz a inicialização dos addons das imagens básicas
	
	al_install_keyboard();																																												//Habilita a entrada via teclado (eventos de teclado), no programa

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);																																					//Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();																																				//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 
	ALLEGRO_FONT* font = al_create_builtin_font();																																						//Carrega uma fonte padrão para escrever na tela (é bitmap, mas também suporta adicionar fontes ttf)
	ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);																																		//Cria uma janela para o programa, define a largura (x) e a altura (y) da tela em píxeis (320x320, neste caso)

	al_register_event_source(queue, al_get_keyboard_event_source());																																	//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(disp));																																	//Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));																																	//Indica que eventos de relógio serão inseridos na nossa fila de eventos

	square* player_1 = square_create(20, 10, Y_SCREEN/2, X_SCREEN, Y_SCREEN);																															//Cria o quadrado do primeiro jogador
	if (!player_1) return 1;																																											//Verificação de erro na criação do quadrado do primeiro jogador
	square* player_2 = square_create(20, X_SCREEN-10, Y_SCREEN/2, X_SCREEN, Y_SCREEN);																													//Cria o quadrado do segundo jogador
	if (!player_2) return 2;																																											//Verificação de erro na criação do quadrado do segundo jogador

	ALLEGRO_EVENT event;																																												//Variável que guarda um evento capturado, sua estrutura é definida em: https:		//www.allegro.cc/manual/5/ALLEGRO_EVENT
	al_start_timer(timer);																																												//Função que inicializa o relógio do programa
	while(1){																																															//Laço principal do programa
		al_wait_for_event(queue, &event);																																								//Função que captura eventos da fila, inserindo os mesmos na variável de eventos

		if (event.type == 30){
			update_position(player_1, player_2);																																						//O evento tipo 30 indica um evento de relógio, ou seja, verificação se a tela deve ser atualizada (conceito de FPS)
			al_clear_to_color(al_map_rgb(0, 0, 0));																																						//Substitui tudo que estava desenhado na tela por um fundo preto
			al_draw_filled_rectangle(player_1->x-player_1->side/2, player_1->y-player_1->side/2, player_1->x+player_1->side/2, player_1->y+player_1->side/2, al_map_rgb(255, 0, 0));					//Insere o quadrado do primeiro jogador na tela
			al_draw_filled_rectangle(player_2->x-player_2->side/2, player_2->y-player_2->side/2, player_2->x+player_2->side/2, player_2->y+player_2->side/2, al_map_rgb(0, 0, 255));					//Insere o quadrado do segundo jogador na tela
    		al_flip_display();																																											//Insere as modificações realizadas nos buffers de tela
		}
		else if ((event.type == 10) || (event.type == 12)){																																				//Verifica se o evento é de botão do teclado abaixado ou levantado (!)
			if (event.keyboard.keycode == 1) joystick_left(player_1->control);																															//Indica o evento correspondente no controle do primeiro jogador (botão de movimentação à esquerda) (!)
			else if (event.keyboard.keycode == 4) joystick_right(player_1->control);																													//Indica o evento correspondente no controle do primeiro jogador (botão de movimentação à direita) (!)
			else if (event.keyboard.keycode == 23) joystick_up(player_1->control);																														//Indica o evento correspondente no controle do primeiro jogador (botão de movimentação para cima) (!)
			else if (event.keyboard.keycode == 19) joystick_down(player_1->control);																													//Indica o evento correspondente no controle do primeiro jogador (botão de movimentação para baixo) (!)
			else if (event.keyboard.keycode == 82) joystick_left(player_2->control);																													//Indica o evento correspondente no controle do segundo jogador (botão de movimentação à esquerda) (!)
			else if (event.keyboard.keycode == 83) joystick_right(player_2->control);																													//Indica o evento correspondente no controle do segundo jogador (botão de movimentação à direita) (!)
			else if (event.keyboard.keycode == 84) joystick_up(player_2->control);																														//Indica o evento correspondente no controle do segundo jogador (botão de movimentação para cima) (!)
			else if (event.keyboard.keycode == 85) joystick_down(player_2->control);																													//Indica o evento correspondente no controle do segundo jogador (botão de movimentação para baixo) (!)
		}
		else if (event.type == 42) break;																																								//Evento de clique no "X" de fechamento da tela. Encerra o programa graciosamente.
	}

	al_destroy_font(font);																																												//Destrutor da fonte padrão
	al_destroy_display(disp);																																											//Destrutor da tela
	al_destroy_timer(timer);																																											//Destrutor do relógio
	al_destroy_event_queue(queue);																																										//Destrutor da fila

	return 0;
}
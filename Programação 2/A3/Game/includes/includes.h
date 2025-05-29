//  BIBLIOTECAS ALLEGRO
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>

//  BIBLIOTECAS PADRÃO
#include <stdio.h>
#include <stdbool.h>

//  HEADERS
#include "game.h"
#include "assets.h"
#include "player.h"
#include "game.h"
#include "projectile.h"
#include "enemy.h"
#include "collision.h"
#include "utils.h"
#include "background.h"


//===========================================================


//  DEFINES

//player.c
#define GRAVIDADE 0.5
#define PULO -12
#define VELOCIDADE 6
#define VIDA_PLAYER 100
#define POSICAO_INICIAL_X 100
#define POSICAO_INICIAL_Y 380
#define ALTURA_CHAO 260
#define ALTURA_SPRITE 32
#define LARGURA_SPRITE 20

//game.h
#define MAX_INIMIGOS 2
#define TELA_LARGURA 900
#define TELA_ALTURA 600
//game.c
#define LARGURA  al_get_display_width(display)
#define ALTURA   al_get_display_height(display)
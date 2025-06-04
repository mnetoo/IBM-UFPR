//  BIBLIOTECAS ALLEGRO
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>

//  BIBLIOTECAS PADRÃO
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//  HEADERS
#include "game.h"
#include "assets.h"
#include "enemy.h"
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
#define GRAVIDADE 0.7
#define PULO -11
#define VELOCIDADE 2
#define VIDA_PLAYER 100
#define POSICAO_INICIAL_Y 380
#define ALTURA_CHAO 470
#define ALTURA_SPRITE 20
#define LARGURA_SPRITE 20

//game
#define MAX_INIMIGOS 6
#define TELA_LARGURA 1200
#define TELA_ALTURA 700
#define NUM_FRAMES_SHOOT 2
#define NUM_FRAMES_CROUCH_AND_SHOOT 2
#define MAX_PROJECTILES 10
#define VELOCIDADE_BULLET 40


#define PLAYER_LARGURA 40
#define PLAYER_ALTURA 60
#define ENEMY_LARGURA 32 * 3.2
#define ENEMY_ALTURA 32 * 3.2
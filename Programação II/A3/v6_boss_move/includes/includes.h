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
#include <math.h>

//  HEADERS
#include "collision.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "projectile.h"
#include "background.h"
#include "boss.h"


//===========================================================


//  DEFINES

//player.c
#define GRAVIDADE 0.7
#define PULO -13
#define VELOCIDADE 3
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
#define VELOCIDADE_BULLET 60

// Direções possíveis
#define SHOOT_DIREITA   0
#define SHOOT_ESQUERDA  1
#define SHOOT_CIMA      2


#define PLAYER_LARGURA 40
#define PLAYER_ALTURA 60
#define ENEMY_LARGURA 32 * 3.2
#define ENEMY_ALTURA 32 * 3.2

#define MAX_ENEMY_PROJECTILES 5
#define MAX_BOSS_PROJECTILES 10

#define DIST_MINIMA 300  // Distância mínima entre inimigos

// Número de quadros por animação
#define NUM_FRAMES_PROJ 3
#define NUM_FRAMES_IDLE 3  // Corrigido para 7 frames
#define NUM_FRAMES_BURN 7
#define BOSS_SHOOT_COOLDOWN 90  // Tempo entre tiros
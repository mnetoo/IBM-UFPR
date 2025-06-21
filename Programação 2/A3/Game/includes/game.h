#ifndef GAME_H
#define GAME_H


//  Estado do jogo
typedef enum 
{
    ESTADO_MENU,
    ESTADO_JOGO,
    ESTADO_GAMEOVER,
    ESTADO_VITORIA,
    ESTADO_SAIR
} EstadoJogo;


//  Função que roda o jogo
EstadoJogo run_game();

//======================================================

//  Função que roda a tela de MENU
EstadoJogo run_menu();

//======================================================

//  Função que roda tela de GAME OVER
EstadoJogo run_gameover();

//======================================================

//  Função que roda tela de VITÓRIA
EstadoJogo run_vitoria();


#endif
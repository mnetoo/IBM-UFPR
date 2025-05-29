#ifndef GAME_H
#define GAME_H

#define MAX_INIMIGOS 2
#define TELA_LARGURA 900
#define TELA_ALTURA 600









typedef enum 
{
    ESTADO_MENU,
    ESTADO_JOGO,
    ESTADO_GAMEOVER,
    ESTADO_VITORIA,
    ESTADO_SAIR
} EstadoJogo;





EstadoJogo run_game();

EstadoJogo run_menu();

EstadoJogo run_gameover();







#endif
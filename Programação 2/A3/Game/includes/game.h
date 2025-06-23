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


/**
 * @brief Função principal que executa o loop do jogo
 * 
 * @return EstadoJogo Próximo estado a ser executado (MENU, GAMEOVER, etc)
 */
EstadoJogo run_game();

//======================================================

/**
 * @brief Executa a tela de menu principal
 * 
 * @return EstadoJogo Próximo estado a ser executado (JOGO ou SAIR)
 */
EstadoJogo run_menu();

//======================================================

/**
 * @brief Executa a tela de game over
 * 
 * @return EstadoJogo Próximo estado (JOGAR NOVAMENTE ou MENU)
 */
EstadoJogo run_gameover();

//======================================================

/**
 * @brief Executa a tela de vitória
 * 
 * @return EstadoJogo Próximo estado (JOGAR NOVAMENTE ou MENU)
 */
EstadoJogo run_vitoria();


#endif
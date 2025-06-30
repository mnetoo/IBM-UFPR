#include "includes.h"

// Variáveis globais estáticas
static ALLEGRO_TIMER *timer;        // Timer para controle de FPS
static ALLEGRO_EVENT_QUEUE *queue;  // Fila de eventos
static ALLEGRO_FONT *font;          // Fonte principal do jogo

// Objetos do jogo
static Player player;               // Instância do jogador
static Enemy inimigos[MAX_INIMIGOS];// Array de inimigos
static Background bg;               // Plano de fundo
static Boss boss;                   // Chefão do jogo

/**
 * @brief Libera todos os recursos alocados do jogo
 * 
 * @param font_pause Fonte usada no menu de pausa
 * @param display Ponteiro para a janela do jogo
 */
void destroy_all(ALLEGRO_FONT *font_pause, ALLEGRO_DISPLAY *display)
{
    printf("\n\nComeçando destruição do jogo...\n\n");

    destroy_player(&player);

    printf("Destruindo inimigos...\n");
    for (int i = 0; i < MAX_INIMIGOS; i++) 
        destroy_enemy(&inimigos[i]);

    printf("Inimigos destruídos com sucesso...\n\n");

    destroy_background(&bg);
    destroy_boss(&boss);

    if (timer)
        al_destroy_timer(timer);
    if (queue)
        al_destroy_event_queue(queue);
    if (font)
        al_destroy_font(font);
    if (font_pause)
        al_destroy_font(font_pause);
    if (display)
        al_destroy_display(display);

    printf("Jogo destruído com sucesso!\n");
}


//===================================================================================================================================================================


/**
 * @brief Função principal que executa o loop do jogo
 * 
 * @return EstadoJogo Próximo estado a ser executado (MENU, GAMEOVER, etc)
 */
EstadoJogo run_game() 
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    bool primeira_vez = true;      // Flag para controle de mensagem
    bool todos_mortos = true;      // Flag para verificar se todos inimigos morreram

    // Configuração inicial da janela
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    if (!display) 
    {
        fprintf(stderr, "Erro ao criar display.\n");
        return ESTADO_SAIR;
    }
    al_set_window_title(display, "GAME");

    // Carrega fontes
    font = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 30, 0);
    if (!font) 
    {
        fprintf(stderr, "Erro ao carregar fonte principal.\n");
        al_destroy_display(display);
        return ESTADO_SAIR;
    }

    ALLEGRO_FONT *font_pause = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 72, 0);
    if (!font_pause) 
    {
        fprintf(stderr, "Erro ao carregar fonte de pausa.\n");
        al_destroy_font(font);
        al_destroy_display(display);
        return ESTADO_SAIR;
    }    

    // Configuração de eventos e timer
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);

    // Registra fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Inicializa objetos do jogo
    init_player(&player);
    init_background(&bg, "./assets/bg/cyberpunk-corridor-PREVIEW.png");
    inicializa_inimigos(inimigos);
    init_boss(&boss, 6000);

    // Variáveis de controle do loop principal
    bool running = true;
    bool redraw = true;
    bool paused = false;
    ALLEGRO_EVENT ev;

    al_start_timer(timer);

    // Loop principal do jogo
    while (running) 
    {
        al_wait_for_event(queue, &ev);

        // Evento de fechar janela
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            destroy_all(font_pause, display);
            return ESTADO_SAIR;
        }

        // Eventos de teclado
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            // Pausa/despausa com P
            if (ev.keyboard.keycode == ALLEGRO_KEY_P) 
            {
                paused = !paused;
                if(paused)
                    printf("Jogo Pausado!\n\n");
            }
            
            // Ignora outros inputs se pausado
            if (paused && ev.keyboard.keycode != ALLEGRO_KEY_P) 
            {
                continue;
            }

            // Volta ao menu com ESC
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
            {
                running = false;
                destroy_all(font_pause, display);
                return ESTADO_MENU;
            }
        }

        // Atualização lógica do jogo (60 FPS)
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (!paused)
            {
                // Atualiza todos os elementos do jogo
                update_player(&player, inimigos, &boss);
                update_background(&bg, player.player_pos_mundo_x);
                update_boss(&boss, player.player_pos_mundo_x, &player);

                // Atualiza inimigos
                for (int i = 0; i < MAX_INIMIGOS; i++)
                    update_enemy(&inimigos[i], player.player_pos_mundo_x, &player);

                // Verifica se todos inimigos morreram
                todos_mortos = true;
                for (int i = 0; i < MAX_INIMIGOS; i++) 
                {
                    if (inimigos[i].ativo)
                        todos_mortos = false;
                }

                // Mensagem sobre chefão
                if(todos_mortos)
                {
                    if(primeira_vez)
                        printf("Todos os inimigos normais morreram!\n\n");
                    primeira_vez = false;
                }


                // Verifica condições de fim de jogo
                if (player.vida <= 0)
                {
                    destroy_all(font_pause, display);
                    return ESTADO_GAMEOVER;
                }

                if (boss.vida <= 0)
                {
                    destroy_all(font_pause, display);
                    return ESTADO_VITORIA;
                }                
            }

            redraw = true; // Marca para redesenhar
        }

        // Renderização
        if (redraw && al_is_event_queue_empty(queue)) 
        {
            redraw = false;

            // Desenha todos os elementos
            draw_background(&bg);
            draw_player(&player);

            if (boss.vida > 0)
                draw_boss(&boss, &player);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                draw_enemy(&inimigos[i]); 

            // HUD do jogo
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Player:   %d", player.vida);
            if(todos_mortos)
                al_draw_textf(font, al_map_rgb(255, 255, 255), TELA_LARGURA - 150, 20, 0, "Boss:   %d", boss.vida);
            
            // Menu de pausa
            if (paused) 
            {
                // Overlay escuro
                al_draw_filled_rectangle(0, 0, TELA_LARGURA, TELA_ALTURA, al_map_rgba(0, 0, 0, 200));
            
                // Texto de pausa
                al_draw_text(font_pause, al_map_rgb(255, 255, 255), 
                             TELA_LARGURA/2, TELA_ALTURA/2 - 90, 
                             ALLEGRO_ALIGN_CENTER, "PAUSE");
            
                // Instruções
                al_draw_text(font, al_map_rgb(128, 0, 170), 
                             TELA_LARGURA/2, TELA_ALTURA/2 + 40, 
                             ALLEGRO_ALIGN_CENTER, "Pressione   P   para   continuar");
            }

            // Atualiza display
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    destroy_all(font_pause, display);
    return ESTADO_MENU;
}



//==============================================================================================================================================================


/**
 * @brief Executa a tela de menu principal
 * 
 * @return EstadoJogo Próximo estado a ser executado (JOGO ou SAIR)
 */
EstadoJogo run_menu() 
{
    al_init_primitives_addon();
    al_init_image_addon();
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Menu");

    ALLEGRO_BITMAP *fundo = al_load_bitmap("./assets/bg/cyberpunk-corridor-PREVIEW.png");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("./assets/fonts/04B_30__.TTF", 85, 0);
    ALLEGRO_FONT *font_opcao = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 35, 0);
    ALLEGRO_FONT *font_instrucoes = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 35, 0);

    if (!fundo || !font_titulo || !font_opcao || !font_instrucoes) 
    {
        printf("Erro ao carregar recursos.\n");
        return ESTADO_SAIR;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    const char* opcoes[] = { "INICIAR   JOGO", "SAIR   DO   JOGO", "COMO   JOGAR" };
    int opcao_selecionada = 0;
    const int total_opcoes = 3;
    bool mostrar_instrucoes = false;

    // Configurações do fundo
    float img_ratio = (float)al_get_bitmap_width(fundo) / (float)al_get_bitmap_height(fundo);
    float screen_ratio = (float)TELA_LARGURA / (float)TELA_ALTURA;
    float zoom_factor = 1.1f;

    bool running = true;
    while (running) 
    {
        // Desenha o fundo (comum para menu e instruções)
        int src_width = al_get_bitmap_width(fundo);
        int src_height = al_get_bitmap_height(fundo);
        
        int crop_w, crop_h;
        if (img_ratio > screen_ratio) 
        {
            crop_h = src_height;
            crop_w = src_height * screen_ratio;
        } 
        else 
        {
            crop_w = src_width;
            crop_h = src_width / screen_ratio;
        }
        
        crop_w = crop_w / zoom_factor;
        crop_h = crop_h / zoom_factor;
        
        int crop_x = (src_width - crop_w) / 2;
        int crop_y = (src_height - crop_h) / 2;

        al_draw_scaled_bitmap(fundo, crop_x, crop_y, crop_w, crop_h, 0, 0, TELA_LARGURA, TELA_ALTURA, 0);
        al_draw_filled_rectangle(0, 0, TELA_LARGURA, TELA_ALTURA, al_map_rgba(0, 0, 0, 150));

        if (mostrar_instrucoes) 
        {
            // Tela de instruções
            al_draw_text(font_titulo, al_map_rgb(255, 255, 255), TELA_LARGURA / 2, 50, ALLEGRO_ALIGN_CENTER, "COMO JOGAR");
            
            // Lista de controles
            const char* controles[] = {
                "PARA   FRENTE  -   Tecla   D",
                "PARA   TRAS  -   Tecla   A",
                "AGACHAR  -     Shift   Esquerdo   ou   Tecla   S",
                "ATIRAR  -     Setas    Direcionais ",
                "PULAR  -     Tecla   W   ou   Space   Bar",
                "PAUSAR  -     Tecla   P",
            };
            
            int start_y = TELA_ALTURA / 3;
            for (int i = 0; i < 4; i++) 
            {
                al_draw_text(font_instrucoes, al_map_rgb(255, 255, 255), 
                            TELA_LARGURA / 2, start_y + i * 40, 
                            ALLEGRO_ALIGN_CENTER, controles[i]);
            }
            
            al_draw_text(font_instrucoes, al_map_rgb(128, 0, 170), 
                        TELA_LARGURA / 2, TELA_ALTURA - 100, 
                        ALLEGRO_ALIGN_CENTER, "Pressione   ESC   para   voltar  ");
        } 
        else 
        {
            // Tela de menu normal
            al_draw_text(font_titulo, al_map_rgb(255, 255, 255), TELA_LARGURA / 2, TELA_ALTURA / 6, ALLEGRO_ALIGN_CENTER, "RUNN GUN");

            for (int i = 0; i < total_opcoes; i++) 
            {
                ALLEGRO_COLOR cor = (i == opcao_selecionada) ? al_map_rgb(128, 0, 170) : al_map_rgb(255, 255, 255);
                al_draw_text(font_opcao, cor, TELA_LARGURA / 2, TELA_ALTURA / 2 + i * 70, ALLEGRO_ALIGN_CENTER, opcoes[i]);
            }
        }

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (mostrar_instrucoes) 
            {
                // Na tela de instruções, apenas ESC tem função
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    mostrar_instrucoes = false;
            
            } 
            else 
            {
                // Na tela de menu normal
                switch (ev.keyboard.keycode) 
                {
                    case ALLEGRO_KEY_UP:
                        opcao_selecionada = (opcao_selecionada - 1 + total_opcoes) % total_opcoes;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        opcao_selecionada = (opcao_selecionada + 1) % total_opcoes;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (opcao_selecionada == 2) // COMO JOGAR
                            mostrar_instrucoes = true;
                        else
                            running = false;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        opcao_selecionada = 1; // sair
                        running = false;
                        break;
                }
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            opcao_selecionada = 1;
            running = false;
        }
    }

    // Limpeza
    al_destroy_bitmap(fundo);
    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_font(font_instrucoes);
    al_destroy_display(display);

    return (opcao_selecionada == 0) ? ESTADO_JOGO : ESTADO_SAIR;
}



//==============================================================================================================================================================


/**
 * @brief Executa a tela de game over
 * 
 * @return EstadoJogo Próximo estado (JOGAR NOVAMENTE ou MENU)
 */
EstadoJogo run_gameover() 
{
    al_init_primitives_addon();
    al_init_image_addon();

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Game Over");

    ALLEGRO_BITMAP *fundo = al_load_bitmap("./assets/bg/cyberpunk-corridor-PREVIEW.png");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("./assets/fonts/04B_30__.TTF", 90, 0);
    ALLEGRO_FONT *font_opcao  = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 50, 0);

    if (!fundo || !font_titulo || !font_opcao) 
    {
        printf("Erro ao carregar imagem ou fontes.\n");
        return ESTADO_SAIR;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    const char* opcoes[] = { "TENTAR   NOVAMENTE", "VOLTAR   AO   MENU" };
    int opcao_selecionada = 0;
    const int total_opcoes = 2;

    // Configurações do fundo (mesmo estilo do menu)
    float img_ratio = (float)al_get_bitmap_width(fundo) / (float)al_get_bitmap_height(fundo);
    float screen_ratio = (float)TELA_LARGURA / (float)TELA_ALTURA;
    float zoom_factor = 1.1f;

    bool running = true;
    while (running) 
    {
        // Recorte e escala do fundo igual ao menu
        int src_width = al_get_bitmap_width(fundo);
        int src_height = al_get_bitmap_height(fundo);

        int crop_w, crop_h;
        if (img_ratio > screen_ratio) {
            crop_h = src_height;
            crop_w = src_height * screen_ratio;
        } else {
            crop_w = src_width;
            crop_h = src_width / screen_ratio;
        }

        crop_w = crop_w / zoom_factor;
        crop_h = crop_h / zoom_factor;

        int crop_x = (src_width - crop_w) / 2;
        int crop_y = (src_height - crop_h) / 2;

        al_draw_scaled_bitmap(fundo, crop_x, crop_y, crop_w, crop_h,
                              0, 0, TELA_LARGURA, TELA_ALTURA, 0);

        // Camada escura semi-transparente
        al_draw_filled_rectangle(0, 0, TELA_LARGURA, TELA_ALTURA, al_map_rgba(0, 0, 0, 150));

        // Título centralizado
        al_draw_text(font_titulo, al_map_rgb(128, 0, 170), TELA_LARGURA / 2, TELA_ALTURA / 6, ALLEGRO_ALIGN_CENTER, "GAME OVER");

        // Opções
        for (int i = 0; i < total_opcoes; i++) 
        {
            ALLEGRO_COLOR cor = (i == opcao_selecionada) ? al_map_rgb(128, 0, 170) : al_map_rgb(255, 255, 255);
            al_draw_text(font_opcao, cor, TELA_LARGURA / 2, TELA_ALTURA / 2 + i * 70, ALLEGRO_ALIGN_CENTER, opcoes[i]);
        }

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            switch (ev.keyboard.keycode) 
            {
                case ALLEGRO_KEY_UP:
                    opcao_selecionada = (opcao_selecionada - 1 + total_opcoes) % total_opcoes;
                    break;
                case ALLEGRO_KEY_DOWN:
                    opcao_selecionada = (opcao_selecionada + 1) % total_opcoes;
                    break;
                case ALLEGRO_KEY_ENTER:
                    running = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    opcao_selecionada = 1; // voltar ao menu
                    running = false;
                    break;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            opcao_selecionada = 1;
            running = false;
        }
    }

    // Limpeza
    al_destroy_bitmap(fundo);
    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_display(display);

    return (opcao_selecionada == 0) ? ESTADO_JOGO : ESTADO_MENU;
}


//==============================================================================================================================================================


/**
 * @brief Executa a tela de vitória
 * 
 * @return EstadoJogo Próximo estado (JOGAR NOVAMENTE ou MENU)
 */
EstadoJogo run_vitoria() 
{
    al_init_primitives_addon();
    al_init_image_addon();

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Vitória");

    ALLEGRO_BITMAP *fundo = al_load_bitmap("./assets/bg/cyberpunk-corridor-PREVIEW.png");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("./assets/fonts/04B_30__.TTF", 90, 0);
    ALLEGRO_FONT *font_opcao  = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 50, 0);

    if (!fundo || !font_titulo || !font_opcao) 
    {
        printf("Erro ao carregar imagem ou fontes.\n");
        return ESTADO_SAIR;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    const char* opcoes[] = { "JOGAR   NOVAMENTE", "VOLTAR   AO   MENU" };
    int opcao_selecionada = 0;
    const int total_opcoes = 2;

    // Configurações do fundo (mesmo estilo do menu)
    float img_ratio = (float)al_get_bitmap_width(fundo) / (float)al_get_bitmap_height(fundo);
    float screen_ratio = (float)TELA_LARGURA / (float)TELA_ALTURA;
    float zoom_factor = 1.1f;

    bool running = true;
    while (running) 
    {
        // Recorte e escala do fundo igual ao menu
        int src_width = al_get_bitmap_width(fundo);
        int src_height = al_get_bitmap_height(fundo);

        int crop_w, crop_h;
        if (img_ratio > screen_ratio) {
            crop_h = src_height;
            crop_w = src_height * screen_ratio;
        } else {
            crop_w = src_width;
            crop_h = src_width / screen_ratio;
        }

        crop_w = crop_w / zoom_factor;
        crop_h = crop_h / zoom_factor;

        int crop_x = (src_width - crop_w) / 2;
        int crop_y = (src_height - crop_h) / 2;

        al_draw_scaled_bitmap(fundo, crop_x, crop_y, crop_w, crop_h,
                              0, 0, TELA_LARGURA, TELA_ALTURA, 0);

        // Camada escura semi-transparente
        al_draw_filled_rectangle(0, 0, TELA_LARGURA, TELA_ALTURA, al_map_rgba(0, 0, 0, 150));

        // Título centralizado
        al_draw_text(font_titulo, al_map_rgb(128, 0, 170), TELA_LARGURA / 2, TELA_ALTURA / 6, ALLEGRO_ALIGN_CENTER, "VITORIA");

        // Opções
        for (int i = 0; i < total_opcoes; i++) 
        {
            ALLEGRO_COLOR cor = (i == opcao_selecionada) ? al_map_rgb(128, 0, 170) : al_map_rgb(255, 255, 255);
            al_draw_text(font_opcao, cor, TELA_LARGURA / 2, TELA_ALTURA / 2 + i * 70, ALLEGRO_ALIGN_CENTER, opcoes[i]);
        }

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            switch (ev.keyboard.keycode) 
            {
                case ALLEGRO_KEY_UP:
                    opcao_selecionada = (opcao_selecionada - 1 + total_opcoes) % total_opcoes;
                    break;
                case ALLEGRO_KEY_DOWN:
                    opcao_selecionada = (opcao_selecionada + 1) % total_opcoes;
                    break;
                case ALLEGRO_KEY_ENTER:
                    running = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    opcao_selecionada = 1; // voltar ao menu
                    running = false;
                    break;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            opcao_selecionada = 1;
            running = false;
        }
    }

    // Limpeza
    al_destroy_bitmap(fundo);
    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_display(display);

    return (opcao_selecionada == 0) ? ESTADO_JOGO : ESTADO_MENU;
}


//==============================================================================================================================================================
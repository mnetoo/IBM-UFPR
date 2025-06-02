#include "includes.h"

static ALLEGRO_TIMER *timer;
static ALLEGRO_EVENT_QUEUE *queue;
static ALLEGRO_FONT *font;

static Player player;
static Enemy inimigos[MAX_INIMIGOS];
static Background bg;


//===================================================================================================================================================================


//  Função que roda o jogo
EstadoJogo run_game() 
{
    srand(time(NULL));
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "GAME");

    float camera_x = player.player_pos_mundo_x - (TELA_LARGURA / 2);

    font = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 20, 0);
    ALLEGRO_FONT *font_pause = al_load_ttf_font("./assets/fonts/ARCAC___.TTF", 72, 0); // Fonte maior para PAUSE

    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    init_player(&player);
    init_background(&bg, "./assets/bg/cyberpunk-corridor-PREVIEW.png");

    printf("Inicializando inimigos...\n");
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        float pos_mundo = 600 + i * 400;
        init_enemy(&inimigos[i], pos_mundo, ALTURA_CHAO);
    }
    printf("Inimigos inicializados com sucesso...\n\n");

    bool running = true;
    bool redraw = true;
    bool paused = false;
    ALLEGRO_EVENT ev;

    al_start_timer(timer);

    while (running) 
    {
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            return ESTADO_SAIR;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_P) 
            {
                paused = !paused;
                if(paused)
                    printf("Jogo Pausado!\n\n");
            }
            
            if (paused && ev.keyboard.keycode != ALLEGRO_KEY_P) 
            {
                continue;
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
            {
                running = false;
                return ESTADO_MENU;
            }
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (!paused)
            {
                update_player(&player);
                update_background(&bg, player.player_pos_mundo_x);

                for (int i = 0; i < MAX_INIMIGOS; i++)
                    update_enemy(&inimigos[i]);

                bool todos_mortos = true;
                for (int i = 0; i < MAX_INIMIGOS; i++) 
                {
                    if (inimigos[i].ativo)
                        todos_mortos = false;
                }

                if (todos_mortos)
                    return ESTADO_VITORIA;

                if (player.vida <= 0)
                    return ESTADO_GAMEOVER;
            }

            redraw = true; // Sempre redesenha, mesmo pausado
        }

        if (redraw && al_is_event_queue_empty(queue)) 
        {
            redraw = false;

            draw_background(&bg);
            draw_player(&player);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                draw_enemy(&inimigos[i], camera_x); 

            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "%d", player.vida);
            
            if (paused) 
            {
                // Escurece o fundo com uma camada semi-transparente
                al_draw_filled_rectangle(0, 0, TELA_LARGURA, TELA_ALTURA, al_map_rgba(0, 0, 0, 200));
            
            
                al_draw_text(font_pause, al_map_rgb(255, 255, 255), 
                             TELA_LARGURA/2, TELA_ALTURA/2 - 90, 
                             ALLEGRO_ALIGN_CENTER, "PAUSE");
            
                // Texto de instrução
                al_draw_text(font, al_map_rgb(128, 0, 170), 
                             TELA_LARGURA/2, TELA_ALTURA/2 + 40, 
                             ALLEGRO_ALIGN_CENTER, "Pressione   P   para   continuar");
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    destroy_player(&player);
    for (int i = 0; i < MAX_INIMIGOS; i++) 
        destroy_enemy(&inimigos[i]);
    destroy_background(&bg);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_font(font_pause);
    al_destroy_display(display);

    return ESTADO_MENU;
}



//==============================================================================================================================================================


// Função que roda a tela de MENU
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
                "MOVIMENTO  -     W   A   S   D",
                "ATIRAR  -     Botao   Esquerdo  do  Mouse",
                "PULAR  -     Space  Bar",
                "PAUSAR  -     Tecla   P",
            };
            
            int start_y = TELA_ALTURA / 3;
            for (int i = 0; i < 5; i++) 
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


//  Função que roda tela de GAME OVER
EstadoJogo run_gameover() 
{
    al_init_primitives_addon();
    al_init_image_addon();

    // Removendo a flag de tela cheia e criando uma janela fixa
    al_set_new_display_flags(ALLEGRO_WINDOWED); // Modo janela (não fullscreen)
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Game Over");

    ALLEGRO_BITMAP *fundo = al_load_bitmap("./assets/bg/level1.png");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("./assets/font1.ttf", 90, 0);
    ALLEGRO_FONT *font_opcao  = al_load_ttf_font("./assets/font1.ttf", 50, 0);

    if (!fundo || !font_titulo || !font_opcao) 
    {
        printf("Erro ao carregar imagem ou fontes.\n");
        return ESTADO_SAIR;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    const char* opcoes[] = { "TENTAR NOVAMENTE", "VOLTAR AO MENU" };
    int opcao_selecionada = 0;
    const int total_opcoes = 2;

    bool running = true;
    while (running) 
    {
        al_draw_scaled_bitmap(fundo, 0, 0, al_get_bitmap_width(fundo), al_get_bitmap_height(fundo),
                              0, 0, TELA_LARGURA, TELA_ALTURA, 0);

        // Título centralizado
        al_draw_text(font_titulo, al_map_rgb(255, 50, 50), TELA_LARGURA / 2, TELA_ALTURA / 6, ALLEGRO_ALIGN_CENTER, "GAME OVER");

        // Opções
        for (int i = 0; i < total_opcoes; i++) 
        {
            ALLEGRO_COLOR cor = (i == opcao_selecionada) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255);
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
                    opcao_selecionada = 1; // Voltar ao menu
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

    al_destroy_bitmap(fundo);
    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_display(display);

    return (opcao_selecionada == 0) ? ESTADO_JOGO : ESTADO_MENU;
}


//==============================================================================================================================================================
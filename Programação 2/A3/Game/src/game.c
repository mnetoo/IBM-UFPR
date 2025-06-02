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
    // Removendo a flag de tela cheia e criando uma janela fixa
    al_set_new_display_flags(ALLEGRO_WINDOWED); // Modo janela (não fullscreen)
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "GAME");

    font = al_load_ttf_font("./assets/font1.ttf", 20, 0);

    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    init_player(&player);
    init_background(&bg, "./assets/bg/cyberpunk-corridor-PREVIEW.png");

    // Inicializa inimigos
    printf("Inicializando inimigos...\n");
    for (int i = 0; i < MAX_INIMIGOS; i++)
        init_enemy(&inimigos[i], 700 + i * 120, 380);
    printf("Inimigos inicializados com sucesso...\n\n");

    bool running = true;
    bool redraw = true;
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

        if (ev.type == ALLEGRO_EVENT_TIMER) 
        {
            update_player(&player);
            update_background(&bg, player.player_pos_mundo_x);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                update_enemy(&inimigos[i]);
    

            // Verificar vitória
            bool todos_mortos = true;
            for (int i = 0; i < MAX_INIMIGOS; i++) 
            {
                if (inimigos[i].ativo)
                    todos_mortos = false;
            }

            if (todos_mortos)
                return ESTADO_VITORIA;

            // Game over se vida zerar
            if (player.vida <= 0)
                return ESTADO_GAMEOVER;

            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(queue)) 
        {
            redraw = false;

            // Desenhar
            draw_background(&bg);
            draw_player(&player);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                draw_enemy(&inimigos[i]);


            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Life: %d", player.vida);
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

    return ESTADO_MENU;
}


//==============================================================================================================================================================


// Função que roda a tela de MENU
EstadoJogo run_menu() 
{
    al_init_primitives_addon();
    al_init_image_addon(); // Para carregar imagem de fundo

    // Removendo a flag de tela cheia e criando uma janela fixa
    al_set_new_display_flags(ALLEGRO_WINDOWED); // Modo janela (não fullscreen)
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Menu");

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

    const char* opcoes[] = { "INICIAR JOGO", "SAIR DO JOGO" };
    int opcao_selecionada = 0;
    const int total_opcoes = 2;

    bool running = true;
    while (running) 
    {
        // Desenha fundo
        al_draw_scaled_bitmap(fundo, 0, 0, al_get_bitmap_width(fundo), al_get_bitmap_height(fundo),
                              0, 0, TELA_LARGURA, TELA_ALTURA, 0);

        // Título
        al_draw_text(font_titulo, al_map_rgb(255, 255, 255), TELA_LARGURA / 2, TELA_ALTURA / 6, ALLEGRO_ALIGN_CENTER, "RUNN GUN");

        // Opções com destaque na selecionada
        for (int i = 0; i < total_opcoes; i++) {
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
                    opcao_selecionada = 1; // sair
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
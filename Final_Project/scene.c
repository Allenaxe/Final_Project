#include "scene.h"

//ALLEGRO_FONT* font = NULL;
ALLEGRO_BITMAP* NewGameButton = NULL;
ALLEGRO_BITMAP* CharaterButton = NULL;
ALLEGRO_BITMAP* menu = NULL;
ALLEGRO_BITMAP* logo = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* pause = NULL;

// function of menu
void menu_init() {
    menu = al_load_bitmap("./image/StartScene0.png");
    logo = al_load_bitmap("./image/logo.png");
    NewGameButton = al_load_bitmap("./image/NewGame.png");
    CharaterButton = al_load_bitmap("./image/Charater.png");
}
void menu_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (400 <= event.mouse.x && event.mouse.x <= 530 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = true;
        if (800 <= event.mouse.x && event.mouse.x <= 930 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = true;
    }
}
void menu_draw() {
    al_draw_bitmap(menu, 0, 0, 0);
    al_draw_bitmap(logo, 50, 50, 0);
    al_draw_bitmap(NewGameButton, 400, 600, 0);
    al_draw_bitmap(CharaterButton, 800, 600, 0);
}
void menu_destroy() {
    al_destroy_bitmap(menu);
    al_destroy_bitmap(logo);
    al_destroy_bitmap(NewGameButton);
    al_destroy_bitmap(CharaterButton);
}

// function of game_scene
void game_scene_init() {
    character_init();
    character_state_init();
    background = al_load_bitmap("./image/stage.jpg");
    pause = al_load_bitmap("./image/pause.png");
}
void game_scene_draw() {
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(pause, 1300, 15, 0);
    character_draw();
    charater_state_draw();
}
void game_scene_destroy() {
    al_destroy_bitmap(background);
    al_destroy_bitmap(pause);
    character_destory();
    charater_state_destory();
}

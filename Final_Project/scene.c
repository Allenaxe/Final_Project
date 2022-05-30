#include "scene.h"

//ALLEGRO_FONT* font = NULL;
//MENU
ALLEGRO_BITMAP* NewGameButton = NULL;
ALLEGRO_BITMAP* CharaterButton = NULL;
ALLEGRO_BITMAP* menu = NULL;
//GAME
ALLEGRO_BITMAP* logo = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* pause = NULL;
ALLEGRO_BITMAP* pause_press = NULL;
//PAUSE
ALLEGRO_BITMAP* PauseUI = NULL;

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
    pause_press = al_load_bitmap("./image/pause_press.png");
}

void game_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (1300 <= event.mouse.x && event.mouse.x <= 1360 && 15 <= event.mouse.y && event.mouse.y <= 60) {
            judge_next_window = true;
        }   
    }
}

void game_scene_draw() {
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(pause, 1300, 15, 0);
    character_draw();
    charater_state_update();  //!!!!!!
}
void game_scene_destroy() {
    al_destroy_bitmap(background);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(pause_press);
    character_destory();
    charater_state_destory();
}

void pause_scene_init() {
    //background = al_load_bitmap("./image/stage.jpg");
    //pause = al_load_bitmap("./image/pause.png");
    //pause_press = al_load_bitmap("./image/pause_press.png");
    PauseUI = al_load_bitmap("./image/PauseUI.png");
}

void pause_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (1300 <= event.mouse.x && event.mouse.x <= 1360 && 15 <= event.mouse.y && event.mouse.y <= 60) {
            judge_next_window = true;
        }
        else if (400 <= event.mouse.x && event.mouse.x <= 500 && 300 <= event.mouse.y && event.mouse.y <= 350) {
            back_to_menu = true;
        }
    }
}

void pause_scene_draw() {
    al_draw_bitmap(PauseUI, 400, 150, 0);
}
void pause_scene_destroy() {
    al_destroy_bitmap(PauseUI);
    /*al_destroy_bitmap(background);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(pause_press);
    character_destory();
    charater_state_destory();*/
}

#include "scene.h"

//ALLEGRO_FONT* font = NULL;
//MENU
ALLEGRO_BITMAP* menu = NULL;
ALLEGRO_BITMAP* NewGameButton = NULL;
ALLEGRO_BITMAP* CharacterButton = NULL;
//GAME
ALLEGRO_BITMAP* Logo= NULL;
ALLEGRO_BITMAP* background = NULL;
//PAUSE
ALLEGRO_BITMAP* PauseUI = NULL;
ALLEGRO_BITMAP* PauseButton = NULL;
ALLEGRO_BITMAP* SettingButton = NULL;
ALLEGRO_BITMAP* PlayButton = NULL;
ALLEGRO_BITMAP* HomeButton = NULL;

// function of menu
void menu_init() {
    menu = al_load_bitmap("./image/StartScene0.png");
    Logo = al_load_bitmap("./image/logo.png");
    NewGameButton = al_load_bitmap("./image/button/NewGameButton.png");
    CharacterButton = al_load_bitmap("./image/button/CharacterButton.png");
}
void menu_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (400 <= event.mouse.x && event.mouse.x <= 530 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = GAME;
        if (800 <= event.mouse.x && event.mouse.x <= 930 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = CHARACTER;
    }
}
void menu_draw() {
    al_draw_bitmap(menu, 0, 0, 0);
    al_draw_bitmap(Logo, 50, 50, 0);
    al_draw_bitmap(NewGameButton, 400, 600, 0);
    al_draw_bitmap(CharacterButton, 800, 600, 0);
}

void menu_destroy() {
    al_destroy_bitmap(menu);
    al_destroy_bitmap(Logo);
    al_destroy_bitmap(NewGameButton);
    al_destroy_bitmap(CharacterButton);
}

// function of game_scene
void game_scene_init() {
    character_init();
    statue_init();
    character_state_init();
    background = al_load_bitmap("./image/stage.jpg");
    PauseButton = al_load_bitmap("./image/button/PauseButton.png");
}

void game_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (1300 <= event.mouse.x && event.mouse.x <= 1360 && 15 <= event.mouse.y && event.mouse.y <= 60) {
            judge_next_window = PAUSE;
        }   
    }
}

void game_scene_draw() {
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(PauseButton, 1300, 15, 0);
    character_draw();
    statue_draw();
    charater_state_update();  //!!!!!!
}
void game_scene_destroy() {
    al_destroy_bitmap(background);
    al_destroy_bitmap(PauseButton);
    character_destory();
    statue_destroy();
    charater_state_destory();
}

void pause_scene_init() {
    PauseUI = al_load_bitmap("./image/PauseUI.png");
    SettingButton = al_load_bitmap("./image/button/SettingButton.png");
    PlayButton = al_load_bitmap("./image/button/PlayButton.png");
    HomeButton = al_load_bitmap("./image/button/HomeButton.png");
}

void pause_process(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (400 <= event.mouse.x && event.mouse.x <= 530 && 475 <= event.mouse.y && event.mouse.y <= 575) {
            judge_next_window = SETTING;
        }
        else if (560 <= event.mouse.x && event.mouse.x <= 750 && 475 <= event.mouse.y && event.mouse.y <= 575) {
            judge_next_window = GAME;
        }
        else if (780 <= event.mouse.x && event.mouse.x <= 890 && 475 <= event.mouse.y && event.mouse.y <= 575) {
            judge_next_window = MENU;
        }
    }
}

void pause_scene_draw() {
    al_draw_bitmap(PauseUI, 400, 150, 0);
    if (button_effect != PAUSE) al_draw_bitmap(PauseButton, 1300, 15, 0);
    if (button_effect != SETTING) al_draw_bitmap(SettingButton, 400, 475, 0);
    if (button_effect != GAME) al_draw_bitmap(PlayButton, 550, 475, 0);
    if (button_effect != MENU) al_draw_bitmap(HomeButton, 768, 475, 0);
}
void pause_scene_destroy() {
    al_destroy_bitmap(PauseUI);
    al_destroy_bitmap(SettingButton);
    al_destroy_bitmap(PlayButton);
    al_destroy_bitmap(HomeButton);
}

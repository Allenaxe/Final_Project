#include "scene.h"
#include "algif5/src/algif.h"//fox

//ALLEGRO_FONT* font = NULL;
//MENU
ALLEGRO_BITMAP* menu = NULL;
ALLEGRO_BITMAP* NewGameButton = NULL;
ALLEGRO_BITMAP* CharacterButton = NULL;
//GAME
int map = 0;
enum {CENTER = 0, CENTER_PROCESS, NORTH, NORTH_PROCESS, EAST, EAST_PROCESS, SOUTH, SOUTH_PROCESS, WEST, WEST_PROCESS, BOSS, BOSS_PROCESS};
ALLEGRO_BITMAP* Logo= NULL;
ALLEGRO_BITMAP* background = NULL;
//PAUSE
ALLEGRO_BITMAP* PauseUI = NULL;
ALLEGRO_BITMAP* PauseButton = NULL;
ALLEGRO_BITMAP* SettingButton = NULL;
ALLEGRO_BITMAP* PlayButton = NULL;
ALLEGRO_BITMAP* HomeButton = NULL;
//ALLEGRO_SAMPLE* song1 = NULL;//fox
//ALLEGRO_SAMPLE_INSTANCE* startsong1;//fox

// function of menu
void menu_init() {
    menu = al_load_bitmap("./image/cover.jpg");
    Logo = al_load_bitmap("./image/logo.png");
    NewGameButton = al_load_bitmap("./image/button/NewGameButton.png");
    CharacterButton = al_load_bitmap("./image/button/CharacterButton.png");
    //fox
    //al_init_acodec_addon();
    //fox
}
void menu_process(ALLEGRO_EVENT event) {
    //fox
    /*song1 = al_load_sample("./sound/Master Yi Champion Select MY BLADE IS YOURS!.mp3");
    startsong1 = al_create_sample_instance(song1);
    al_set_sample_instance_playmode(startsong1,ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startsong1,al_get_default_mixer());*/
    //fox
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (400 <= event.mouse.x && event.mouse.x <= 530 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = GAME;
            //al_play_sample_instance(startsong1);
        if (800 <= event.mouse.x && event.mouse.x <= 930 && 600 <= event.mouse.y && event.mouse.y <= 660)
            judge_next_window = CHARACTER;
    }
}
void menu_draw(){
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
    //al_stop_sample_instance(startsong1);
}

// function of game_scene
void game_scene_init() {
    int map = 0;
    character_init();
    statue_init();
    character_state_init();
    background = al_load_bitmap("./image/background 1.jpg");
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

    if (map == CENTER_PROCESS) {
        map = CENTER;
        monster_destroy();
        map_free();
        statue_init();
    }

    if (map == CENTER) {
        statue_draw();
        if(key_state[ALLEGRO_KEY_W] && chara_pos_y <= 0) {
            map = NORTH_PROCESS;
            chara_pos_y = 768;
        }
        if(key_state[ALLEGRO_KEY_D] && chara_pos_x >= 1266) {
            map = EAST_PROCESS;
            chara_pos_x = 0;
        }
        if(key_state[ALLEGRO_KEY_S] && chara_pos_y >= 650) {
            map = SOUTH_PROCESS;
            chara_pos_y = 0;
        }
        if(key_state[ALLEGRO_KEY_A] && chara_pos_x <= 0) {
            map = WEST_PROCESS;
            chara_pos_x = 1366;
        }
    }

    if (map == NORTH_PROCESS) {
        map = NORTH;
        map_free();
        monster_init();
    }

    if (map == NORTH) {
        monster_update();
        monster_draw();
        if(key_state[ALLEGRO_KEY_S] && chara_pos_y >= 650) {
            map = CENTER_PROCESS;
            chara_pos_y = 0;
        }
        else map = NORTH;
    }

    if (map == EAST_PROCESS) {
        map = EAST;
        map_free();
        monster_init();
    }

    if (map == EAST) {
        monster_update();
        monster_draw();
        if(key_state[ALLEGRO_KEY_A] && chara_pos_x <= 0) {
            map = CENTER_PROCESS;
            chara_pos_x = 1366;
        }
        else map = EAST;
    }

    if (map == SOUTH_PROCESS) {
        map = SOUTH;
        map_free();
        shop_init();
    }

    if (map == SOUTH){
        shop_draw();
        if(key_state[ALLEGRO_KEY_W] && chara_pos_y <= 0) {
            map = CENTER_PROCESS;
            chara_pos_y = 768;
        }
        else map = SOUTH;
    }

    if (map == WEST_PROCESS) {
        map = WEST;
        map_free();
        monster_init();
    }

    if (map == WEST) {
        monster_update();
        monster_draw();
        if(key_state[ALLEGRO_KEY_D] && chara_pos_x >= 1266) {
            map = CENTER_PROCESS;
            chara_pos_x = 0;
        }
        else map = WEST;
    }
}
void game_scene_destroy() {
    al_destroy_bitmap(background);
    al_destroy_bitmap(PauseButton);
    character_destory();
    monster_destroy();
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

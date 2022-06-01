#include "charater.h"

// the state of character
enum { STOP = 0, MOVE, ATK };
typedef struct character
{
    char name[10];
    int x, y; // the position of image
    int coin;
    int blood;
    int magic;
    int attack;
    int defence;
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP* img_move[2];
    ALLEGRO_BITMAP* img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE* atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;

typedef struct character_state
{
    ALLEGRO_BITMAP* UI;
    ALLEGRO_BITMAP* img_blood[5];
    ALLEGRO_BITMAP* img_defence[5];
    ALLEGRO_BITMAP* img_magic[5];
}Character_State;

Character chara = {.name = "character\0"};
Character_State chara_state;
ALLEGRO_SAMPLE* sample = NULL;

void character_init() {
    // load character images
    for (int i = 1; i <= 2; i++) {
        char temp[50];
        sprintf_s(temp, 50, "./image/char_move%d.png", i);
        chara.img_move[i - 1] = al_load_bitmap(temp);
    }
    for (int i = 1; i <= 2; i++) {
        char temp[50];
        sprintf_s(temp, 50, "./image/char_atk%d.png", i);
        chara.img_atk[i - 1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.coin = 0;
    chara.blood = 5;
    chara.magic = 180;
    chara.defence = 5;
    chara.attack = 5;
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH / 2 + 100;
    chara.y = HEIGHT / 2;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

    object_construct(chara.name, chara.x, chara.x + 120, chara.y + 115, chara.y);
}
void charater_process(ALLEGRO_EVENT event) {
    // process the animation
    if (event.type == ALLEGRO_EVENT_TIMER) {
        if (event.timer.source == fps) {
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
        // process the keyboard event
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (collision == 4 && chara.coin >= 15) {
            chara.coin -= 15;
            chara.attack += 5;
        }
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update() {
    // use the idea of finite state machine to deal with different state
    collision = collision_judge(chara.name, chara.x, chara.x + 100, chara.y + 100, chara.y);
    if (key_state[ALLEGRO_KEY_W] && chara.y >= 0 && collision != 4) {
        chara.y -= 2;
        chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_A] && chara.x >= 0 && collision != 2) {
        chara.dir = false;
        chara.x -= 2;
        chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_S] && chara.y <= HEIGHT - 100 && collision != 3) {
        chara.y += 2;
        chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_D] && chara.x <= WIDTH - 100 && collision != 1) {
        chara.dir = true;
        chara.x += 2;
        chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_SPACE]) {
        chara.state = ATK;
    }
    else if (chara.anime == chara.anime_time - 1) {
        chara.anime = 0;
        chara.state = STOP;
    }
    else if (chara.anime == 0) {
        chara.state = STOP;
    }
    collision_update(chara.name, chara.x, chara.x + 120, chara.y + 115, chara.y);
    collision = 0;
}
void character_draw() {
    // with the state, draw corresponding image
    if (chara.state == STOP) {
        if (chara.dir)
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }
    else if (chara.state == MOVE) {
        if (chara.dir) {
            if (chara.anime < chara.anime_time / 2) {
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else {
            if (chara.anime < chara.anime_time / 2) {
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }
            else {
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }
    else if (chara.state == ATK) {
        if (chara.dir) {
            if (chara.anime < chara.anime_time / 2) {
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
        else {
            if (chara.anime < chara.anime_time / 2) {
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }
            else {
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }
}
void character_destory() {
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}

void character_state_init() {
    chara_state.UI = al_load_bitmap("./image/UI.png");
    for (int i = 1; i <= 5; ++i) {

        char temp[50];
        sprintf_s(temp, 50, "./image/blood/blood_%d.png", i);
        chara_state.img_blood[i - 1] = al_load_bitmap(temp);
    }
    for (int i = 1; i <= 5; ++i) {
        char temp[50];
        sprintf_s(temp, 50, "./image/defence/defence_%d.png", i);
        chara_state.img_defence[i - 1] = al_load_bitmap(temp);
    }
    /*for (int i = 1; i <= 5; ++i) {
        char temp[50];
        sprintf_s(temp, 50, "./image/magic/magic_%d.png", i);
        chara_state.img_blood[i - 1] = al_load_bitmap(temp);
    }*/
    chara_state.img_magic[4] = al_load_bitmap("./image/magic/magic_5.png");
}

void charater_state_update() {
    al_draw_bitmap(chara_state.UI, 5, 5, 0);
    if (chara.blood == 5) al_draw_bitmap(chara_state.img_blood[4], 43.75, 13.75, 0);
    else if (chara.blood == 4) al_draw_bitmap(chara_state.img_blood[3], 43.75, 13.75, 0);
    else if (chara.blood == 3) al_draw_bitmap(chara_state.img_blood[2], 43.75, 13.75, 0);
    else if (chara.blood == 2) al_draw_bitmap(chara_state.img_blood[1], 43.75, 13.75, 0);
    else if (chara.blood == 1) al_draw_bitmap(chara_state.img_blood[0], 43.75, 13.75, 0);
    else;
    if (chara.defence == 5)  al_draw_bitmap(chara_state.img_defence[4], 43.75, 41.75, 0);
    else if (chara.defence == 4)  al_draw_bitmap(chara_state.img_defence[3], 43.75, 41.75, 0);
    else if (chara.defence == 3)  al_draw_bitmap(chara_state.img_defence[2], 43.75, 41.75, 0);
    else if (chara.defence == 2)  al_draw_bitmap(chara_state.img_defence[1], 43.75, 41.75, 0);
    else if (chara.defence == 1)  al_draw_bitmap(chara_state.img_defence[0], 43.75, 41.75, 0);
    else;
    if (chara.magic == 180) {
        al_draw_bitmap(chara_state.img_magic[4], 43.75, 69.75, 0);
    }
}

void charater_state_destory() {
    al_destroy_bitmap(chara_state.UI);
    for (int i = 0; i < 5; ++i) {
        al_destroy_bitmap(chara_state.img_blood[i]);
    }
    for (int i = 0; i < 5; ++i) {
        al_destroy_bitmap(chara_state.img_defence[i]);
    }
    al_destroy_bitmap(chara_state.img_magic[4]);
}
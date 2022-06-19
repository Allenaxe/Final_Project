#include "charater.h"
#include"object.h"
// the state of character
enum { ROLE_1  = 0, ROLE_2};
enum { STOP = 0, MOVE, ATK };

int bloodcount = 0;

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
    int role;
    ALLEGRO_BITMAP* img_move[4];
    ALLEGRO_BITMAP* img_atk[4];
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

typedef struct attribute {
    char name[50];
	int x, y;
}Attribute;

typedef struct SUPPLEMENT{
    ALLEGRO_BITMAP *image;
    Attribute* item;
}SUPPLEMENT;

typedef struct MAGIC{
    ALLEGRO_BITMAP *image;
    Attribute* item;
}MAGIC;

SUPPLEMENT supplement;
MAGIC magic;

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
    chara.blood = 500;
    chara.magic = 180;
    chara.defence = 5;
    chara.attack = 5;
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = chara_pos_x = WIDTH / 2 + 100;
    chara.y = chara_pos_y = HEIGHT / 2;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.role = ROLE_1;
    chara.anime = 0;
    chara.anime_time = 30;

    object_construct(chara.name, chara.x, chara.x + 100, chara.y + 100, chara.y);
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
    chara.x = chara_pos_x; chara.y = chara_pos_y;
    if(chara_lose_blood && bloodcount == 0) {chara.blood -= chara_lose_blood; ++bloodcount;}
    else if(bloodcount == 180) bloodcount = 0;
    else ++bloodcount;
    chara_lose_blood = 0;
    collision = collision_judge(chara.name, chara.x, chara.x + 100, chara.y + 100, chara.y);
    DATK = false;
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
        DATK = true;
        chara.state = ATK;
    }
    else if (chara.anime == chara.anime_time - 1) {
        chara.anime = 0;
        chara.state = STOP;
    }
    else if (chara.anime == 0) {
        chara.state = STOP;
    }

    chara_pos_x = chara.x; chara_pos_y = chara.y;

    collision_update(chara.name, chara.x, chara.x + 100, chara.y + 100, chara.y);

    collision = 0;
}





void character_draw() {
    // with the state, draw corresponding image
    if (chara.role == 0){
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
    if (chara.blood == 500) al_draw_bitmap(chara_state.img_blood[4], 43.75, 13.75, 0);
    else if (chara.blood == 400) al_draw_bitmap(chara_state.img_blood[3], 43.75, 13.75, 0);
    else if (chara.blood == 300) al_draw_bitmap(chara_state.img_blood[2], 43.75, 13.75, 0);
    else if (chara.blood == 200) al_draw_bitmap(chara_state.img_blood[1], 43.75, 13.75, 0);
    else if (chara.blood == 100) al_draw_bitmap(chara_state.img_blood[0], 43.75, 13.75, 0);
    else;
    if (chara.defence == 500)  al_draw_bitmap(chara_state.img_defence[4], 43.75, 41.75, 0);
    else if (chara.defence == 400)  al_draw_bitmap(chara_state.img_defence[3], 43.75, 41.75, 0);
    else if (chara.defence == 300)  al_draw_bitmap(chara_state.img_defence[2], 43.75, 41.75, 0);
    else if (chara.defence == 200)  al_draw_bitmap(chara_state.img_defence[1], 43.75, 41.75, 0);
    else if (chara.defence == 100)  al_draw_bitmap(chara_state.img_defence[0], 43.75, 41.75, 0);
    else;
    if (chara.magic == 180) {
        al_draw_bitmap(chara_state.img_magic[4], 43.75, 69.75, 0);
    }
}

void charater_state_destory() {
    al_destroy_bitmap(chara_state.UI);
    for (int i = 0; i < 5; ++i) al_destroy_bitmap(chara_state.img_blood[i]);
    for (int i = 0; i < 5; ++i) al_destroy_bitmap(chara_state.img_defence[i]);
    al_destroy_bitmap(chara_state.img_magic[4]);
}

void item_init(){
    supplement.image = al_load_bitmap("./image/item/mbp.png");
    magic.image = al_load_bitmap("./image/item/mph.png");

}
/*void supplement_func(){
    if(collision_judge(shop.name,shop.BorderLeft, shop.BorderRight, shop.BorderUp, shop.BorderDown) != 0 && money >= 10 && key_state[ALLEGRO_KEY_SPACE]){
        chara.blood += 1;
        chara.coin -= 10;
   }
}
void magic_func(){
    if((collision_judge(shop.name,shop.BorderLeft, shop.BorderRight, shop.BorderUp, shop.BorderDown) != 0 money >= 10&& key_state[ALLEGRO_KEY_W]){
        chara.magic += 1;
        chara.coin -= 10;
    }
    if(chara.defence==5&&key_state[ALLEGRO_KEY_SPACE]){
        for(int i=0;i<=size;i++){
                if((New.group[i].x-chara.x<200&&New.group[i].x-chara.x>-200)||(New.group[i].y-chara.y<200&&New.group[i].y-chara.y>-200))
                   strcpy_s(New.group[i].name, 50, "died\0");
                }

    }
}*/

void shop_func(){

}

/*int blood_control(){
    for(int i=0;i<=size;i++){
  if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)!=0){
        if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==1&&(chara_state!=ATK||key_state[ALLEGRO_KEY_D]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
        if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==2&&(chara_state!=ATK||key_state[ALLEGRO_KEY_A]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
        if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==3&&(chara_state!=ATK||key_state[ALLEGRO_KEY_s]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
        if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==4&&(chara_state!=ATK||key_state[ALLEGRO_KEY_w]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
    }
  }
  if(collision_judge(bigboss.name,chara.x,chara.x + 50,chara.y + 50, chara.y)!=0){
        if(collision_judge(New.bigboss.name,chara.x,chara.x + 50,chara.y + 50, chara.y)==1&&(chara_state!=ATK||key_state[ALLEGRO_KEY_D]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
        if(collision_judge(New.bigboss.name,chara.x,chara.x + 50,chara.y + 50, chara.y)==2&&(chara_state!=ATK||key_state[ALLEGRO_KEY_A]!=0)){
        chara.blood=chara.blood-1;//adjust
        if(collision_judge(New.bigboss.name,chara.x,chara.x + 50,chara.y + 50, chara.y)==3&&(chara_state!=ATK||key_state[ALLEGRO_KEY_s]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
        if(collision_judge(New.bigboss.name,chara.x,chara.x + 50,chara.y + 50, chara.y)==4&&(chara_state!=ATK||key_state[ALLEGRO_KEY_w]!=0)){
        chara.blood=chara.blood-1;//adjust
    }
    }

}*/


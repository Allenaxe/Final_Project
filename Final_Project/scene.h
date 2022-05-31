#include "global.h"
#include "charater.h"
#include "object.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init();
void game_process(ALLEGRO_EVENT event);
void game_scene_draw();
void game_scene_destroy();

void pause_scene_init();
void pause_process(ALLEGRO_EVENT event);
void pause_scene_draw();
void pause_scene_destroy();
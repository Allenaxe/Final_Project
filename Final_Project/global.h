#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool atk;
extern int judge_next_window;
extern int button_effect;
extern int collision;
enum { DEFAULT = 0, MENU = 1, PROCESS = 2, GAME = 3, CHARACTER = 4, PAUSE = 5, SETTING = 6 };
extern int window;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_TIMER* fps;
#endif

/* 

¸I¼²½c

CHARACTER : (0, 120, 115, 0)
MONSTER : (0, 50, 50, 0)
STATUE : (0, 110, 190, 0)

*/
#include "effect.h"

ALLEGRO_BITMAP* PauseButton = NULL;
ALLEGRO_BITMAP* PausePressButton = NULL;

int count = 0;

void button_effect_init() {
	PauseButton = al_load_bitmap("./image/pause.png");
	PausePressButton = al_load_bitmap("./image/pause_press.png");
}

void button_effect_update(ALLEGRO_EVENT event) {
	if (judge_next_window == PAUSE) button_effect = PAUSE;
	if (event.type == ALLEGRO_EVENT_TIMER) if (event.timer.source == fps)  ++count;
	if (count == 60) count = 0;
	if (button_effect == PAUSE) {
		al_draw_bitmap(PausePressButton, 1300, 15, 0);
		if (!count) button_effect = DEFAULT;
	}
	else al_draw_bitmap(PauseButton, 1300, 15, 0);
}

void button_effect_destroy() {
	al_destroy_bitmap(PauseButton);
	al_destroy_bitmap(PausePressButton);
}
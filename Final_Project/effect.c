#include "effect.h"

ALLEGRO_BITMAP* NewGamePressButton = NULL;
ALLEGRO_BITMAP* PausePressButton = NULL;
ALLEGRO_BITMAP* SettingPressButton = NULL;
ALLEGRO_BITMAP* PlayPressButton = NULL;
ALLEGRO_BITMAP* HomePressButton = NULL;

int count = 0;

void button_effect_init() {
	
	NewGamePressButton = al_load_bitmap("./image/button/NewGamePressDown.png");
	PausePressButton = al_load_bitmap("./image/button/PausePressDown.png");
	SettingPressButton = al_load_bitmap("./image/button/SettingPressDown.png");
	PlayPressButton = al_load_bitmap("./image/button/PlayPressDown.png");
	HomePressButton = al_load_bitmap("./image/button/HomePressDown.png");
}

void button_effect_update(ALLEGRO_EVENT event) {
	if (judge_next_window != DEFAULT) button_effect = judge_next_window;
	if (event.type == ALLEGRO_EVENT_TIMER) if (event.timer.source == fps)  ++count;
	if (count == 60) count = 0;

	if (button_effect == GAME && window == MENU) {
		al_draw_bitmap(NewGamePressButton, 400, 600, 0);
		if (!count) button_effect = DEFAULT;
	}

	if (button_effect == CHARACTER) {
		//al_draw_bitmap(CharacterButton, 800, 600, 0);  //!!!!!!!
		if (!count) button_effect = DEFAULT;
	}

	if (button_effect == PAUSE) {
		al_draw_bitmap(PausePressButton, 1300, 15, 0);
		if (!count) button_effect = DEFAULT;
	}

	if (button_effect == SETTING) {
		al_draw_bitmap(SettingPressButton, 400, 475, 0);
		if (!count) button_effect = DEFAULT;
	}

	if (button_effect == GAME && window == PAUSE) {
		al_draw_bitmap(PlayPressButton, 550, 475, 0);
		if (!count) button_effect = DEFAULT;
	}

	if (button_effect == MENU) {
		al_draw_bitmap(HomePressButton, 768, 475, 0);
		if (!count) button_effect = DEFAULT;
	}
}

void button_effect_destroy() {
	al_destroy_bitmap(NewGamePressButton);
	al_destroy_bitmap(PausePressButton);
	al_destroy_bitmap(SettingPressButton);
	al_destroy_bitmap(PlayPressButton);
	al_destroy_bitmap(HomePressButton);
}
#include "object.h"

typedef struct STATUE {
	ALLEGRO_BITMAP* Statue;
	ALLEGRO_BITMAP* StatueTalk;
	int border_x_left, border_x_right, border_y_up, border_y_down;
}STATUE;

STATUE STATUE_1;

void statue_init() {
	STATUE_1.Statue = al_load_bitmap("./image/statue/statue1.png");
	STATUE_1.StatueTalk = al_load_bitmap("./image/statue/statuetalk.png");
	char tmp[10] = "statue1\0";
	object_construct(tmp, WIDTH / 2 - 90, WIDTH / 2 + 20, HEIGHT / 2 + 100, HEIGHT / 2 - 90);
}

void statue_trigger() {
	al_draw_bitmap(STATUE_1.StatueTalk, WIDTH / 2 - 50, HEIGHT / 2 - 200, 0);
}

void statue_draw() {
	al_draw_bitmap(STATUE_1.Statue, WIDTH / 2 -100, HEIGHT / 2 - 100, 0);
}

void statue_destroy() {
	al_destroy_bitmap(STATUE_1.Statue);
	al_destroy_bitmap(STATUE_1.StatueTalk);
}
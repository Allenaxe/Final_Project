#include "global.h"

void object_construct(char *src, int B_X_UL, int B_X_UR, int B_Y_DL, int B_Y_UL);
void collision_update(char *src, int A_X_UL, int A_X_UR, int A_Y_DL, int A_Y_UL);
void object_free();
int collision_judge(char *src, int A_X_UL, int A_X_UR, int A_Y_DL, int A_Y_UL);

void statue_init();
void statue_trigger();
void statue_draw();
void statue_destroy();
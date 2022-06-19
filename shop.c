#include "shop.h"

ALLEGRO_BITMAP *SHOP_IMAGE;

void shop_init(){
    SHOP_IMAGE = al_load_bitmap("./image/shop.png");
    object_construct("shop\0", WIDTH / 2 - 100, WIDTH / 2 + 40, HEIGHT / 2 + 40, HEIGHT / 2 - 100);
    //sprintf_s(shop.name, 1, "shop%d\0", 0 );
}

void shop_draw(){
    al_draw_bitmap(SHOP_IMAGE, WIDTH / 2 - 100, HEIGHT / 2 - 100, 0);
}

void shop_destroy(){
    al_destroy_bitmap(SHOP_IMAGE);
}

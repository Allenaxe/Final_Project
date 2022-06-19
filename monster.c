#include "object.h"

typedef struct attribute
{
    char name[50];
    int x, y;
    int blood;
    bool direction;
    int walk;
} Attribute;

typedef struct monster
{
    ALLEGRO_BITMAP* MONSTER;
    Attribute* group;
} Monster;

int size;
Monster New;

void monster_init()
{
    New.group = (Attribute *)calloc(25, sizeof(Attribute));
    New.MONSTER = al_load_bitmap("./image/monster/monster1.png");
    srand(time(NULL));
    size = 6 + rand() % 5;
    printf("%d", size);
    for (int i = 0; i <= size; ++i)
    {
        if (New.group != NULL)
        {
            sprintf_s(New.group[i].name, 50, "monster%d\0", i);
            New.group[i].x = rand() % 1316;
            New.group[i].y = rand() % 718;
            New.group[i].blood = 100 + rand() % 10;
            New.group[i].direction = (rand() % 2) ? true : false;
            New.group[i].walk = rand() % 8;
            object_construct(New.group[i].name, New.group[i].x, New.group[i].x + 50, New.group[i].y + 50, New.group[i].y);
        }
    }
}

void monster_update()
{
    for (int i = 0; i <= size; ++i)
    {
        int count = rand() % 180;
        int dir = (count == 0)? rand() % 8 : New.group[i].walk;
        New.group[i].walk = dir;
        int monster_collision = collision_judge(New.group[i].name, New.group[i].x, New.group[i].x + 50, New.group[i].y + 50, New.group[i].y);
        if (dir == 0)
        {
            if (New.group[i].y <= 0 || monster_collision == 4)
            {
                New.group[i].walk = 2;
                return;
            }
            New.group[i].y -= 1;
        }
        else if (dir == 1)
        {
            if (New.group[i].x <= 0 || monster_collision == 2)
            {
                New.group[i].walk = 3;
                return;
            }
            New.group[i].direction = false;
            New.group[i].x -= 1;
        }
        else if (dir == 2)
        {
            if (New.group[i].y > 725 || monster_collision == 3)
            {
                New.group[i].walk = 0;
                return;
            }
            New.group[i].y += 1;
        }
        else if (dir == 3)
        {
            if (New.group[i].x > 1300 || monster_collision == 1)
            {
                New.group[i].walk = 1;
                return;
            }
            New.group[i].direction = true;
            New.group[i].x += 1;
        }
        else if (dir == 4)
        {
            if (New.group[i].x <= 0 || New.group[i].y <= 0 || monster_collision == 4 || monster_collision == 2)
            {
                New.group[i].walk = 7;
                return;
            }
            New.group[i].x -= 1;
            New.group[i].y -= 1;
        }
        else if (dir == 5)
        {
            if (New.group[i].x <= 0 || New.group[i].y > 718 || monster_collision == 2 || monster_collision == 3)
            {
                New.group[i].walk = 6;
                return;
            }
            New.group[i].direction = false;
            New.group[i].x -= 1;
            New.group[i].y += 1;
        }
        else if (dir == 6)
        {
            if (New.group[i].x > 1316 || New.group[i].y <= 0 || monster_collision == 1 || monster_collision == 4)
            {
                New.group[i].walk = 5;
                return;
            }
            New.group[i].x += 1;
            New.group[i].y -= 1;
        }
        else if (dir == 7)
        {
            if (New.group[i].x > 1316 || New.group[i].y > 725 || monster_collision == 1 || monster_collision == 3)
            {
                New.group[i].walk = 4;
                return;
            }
            New.group[i].direction = true;
            New.group[i].x += 1;
            New.group[i].y += 1;
        }
        /*else if (chara.anime == chara.anime_time - 1) {
            chara.anime = 0;
            chara.state = STOP;
        }
        else if (chara.anime == 0) {
            chara.state = STOP;
        }*/
        collision_update(New.group[i].name, New.group[i].x, New.group[i].x + 50, New.group[i].y + 50, New.group[i].y);
    }
}

int monster_delete(char* src)
{
    if (DATK == false) return 0;
    for (int i = 0; i <= size; ++i)
    {
        if (!strcmp(src, New.group[i].name))
        {
            if (New.group[i].blood > 5)
            {
                New.group[i].blood -= 5;
                return 0;
            }
            else
            {
                strcpy_s(New.group[i].name, 50, "died\0");
                return 1;
            }
        }
    }
    return 2;
}

void monster_draw()
{
    for (int i = 0; i <= size; ++i)
    {
        if(strcmp(New.group[i].name, "died"))
            al_draw_bitmap(New.MONSTER, New.group[i].x, New.group[i].y, New.group[i].direction);
    }
}

void monster_destroy()
{
    free(New.group);
    al_destroy_bitmap(New.MONSTER);
}

//000000
/*void bigboss_init()
{   for(int i=0;i<=50;i++){
    if((strcmp(New.group[i].name, "died"))
      count++;
      if(count==50){
    New.bigboss= (Attribute *)calloc(1, sizeof(Attribute));
    New.bigboss = al_load_bitmap(" ");
    sprintf_s(New.bigboss.name, 1, "monster%d\0", 0);
    New.bigboss.x=1300;
    New.bigboss.y=500;
    New.bigboss.blood=500;
    New.bigboss.direction= (rand() % 2) ? true : false;
    New.bigboss.walk = rand() % 8;;
    object_construct(New.bigboss.name; New.bigboss.x; New.bigboss.x+100; New.bigboss.y+100; New.bigboss.y);
      }
    }
    if(strcmp(New.group[i].name, "died")==0)break;

}
void bigboss_destroy()
{
    free(New.bigboss);
    al_destroy_bitmap(New.bigboss);
}


void bigboss_blood_control()
{
    if(collision_judge(chara,New.bigboss.x, New.bigboss.x + 200, New.bigboss.y + 200, New.bigboss.y)!=0)
    {
        if(collision_judge(chara.name,New.bigboss.x, New.bigboss.x + 200, New.bigboss.y + 200, New.bigboss.y)==1&&(chara_state!=ATK||key_state[ALLEGRO_KEY_A]!=0))
        {
            New.bigboss.blood=New.bigboss.blood-50;
        }
        if(collision_judge(chara.name,New.bigboss.x, New.bigboss.x + 200, New.bigboss.y + 200, New.bigboss.y)==2&&(chara_state!=ATK||key_state[ALLEGRO_KEY_D]!=0)))
        {
            New.bigboss.blood=New.bigboss.blood-50;
        }
        if(collision_judge(chara.name,New.bigboss.x, New.bigboss.x + 200, New.bigboss.y + 200, New.bigboss.y)==3&&(chara_state!=ATK||key_state[ALLEGRO_KEY_W]!=0)))
        {
            New.bigboss.blood=New.bigboss.blood-50;
        }
        if(collision_judge(chara.name,New.bigboss.x, New.bigboss.x + 200, New.bigboss.y + 200, New.bigboss.y)==4&&(chara_state!=ATK||key_state[ALLEGRO_KEY_S]!=0)))
        {
            New.bigboss.blood=New.bigboss.blood-50;
        }
    }
    if(bigboss.blood<=0) bigboss_destory();
}

if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)!=0)
{
    if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==1&&(chara_state!=ATK||key_state[ALLEGRO_KEY_D]!=0))
    {
        chara.blood=chara.blood-1;//adjust
    }
    if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==2&&(chara_state!=ATK||key_state[ALLEGRO_KEY_A]!=0))
    {
        chara.blood=chara.blood-1;//adjust
    }
    if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==3&&(chara_state!=ATK||key_state[ALLEGRO_KEY_s]!=0))
    {
        chara.blood=chara.blood-1;//adjust
    }
    if(collision_judge(New.group[i].name,chara.x,chara.x + 50,chara.y + 50, chara.y)==4&&(chara_state!=ATK||key_state[ALLEGRO_KEY_w]!=0))
    {
        chara.blood=chara.blood-1;//adjust
    }
}*/

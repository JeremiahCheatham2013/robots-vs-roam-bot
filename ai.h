#ifndef AI_H
#define AI_H

#include "main.h"
#include "player.h"

struct Enemy{
    int x;
    int y;
    int alive;
    int cycle;
    int dir; 
};

struct Enemy * enemy_new(int x, int y);
int update_enemy(struct Enemy * enemy, struct Player * player, int player_lives, int speed);
int draw_enemy(struct Enemy * enemy);

#endif

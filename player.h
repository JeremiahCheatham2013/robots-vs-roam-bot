#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

struct Player{
    int x;
    int y;
    int rank;
    int dir;
};

struct Player * player_new(int rank, int x, int y);
int player_update(int rank, char keypress, struct Player * player);
int player_draw(int rank, char keypress, struct Player * player);

#endif

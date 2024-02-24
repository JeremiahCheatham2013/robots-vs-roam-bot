#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

struct Level{
    int width;
    int height;
    char map[50][50];
};

struct Level build_level(int rank);
int show_grave(void);
int clear_screen(void);

#endif

#include "player.h"
#include <stdlib.h>

struct Player* player_new(int rank, int x, int y){
    struct Player * player;
    player = calloc(1, sizeof(struct Player));
    player->rank = rank;
    player->x = x;
    player->y = y;
    player->dir = 1;
    return player;
}

int player_update(int rank, char keypress, struct Player * player){ 
    if (player == NULL){
        return 1;
    }
    mvprintw(player->y, player->x - 1, "   ");
    mvprintw(player->y - 1, player->x - 1, "   ");
    if (player->dir == 1){
        mvprintw(player->y + 1, player->x, "     ");
    }else{
        mvprintw(player->y + 1, player->x - 4, "     ");
    }
    mvprintw(player->y + 2, player->x, " ");
    mvprintw(2, 0, "rank: %d", rank);

    switch (keypress) {
        case 'w':
            if (player->y > 30 || player->x < 33 || player->x > 58 || player->y < 20)
            player->y--;
            break;

        case 's': 
            if (player->y < 17 || player->x < 33 || player->x > 58 || player->y > 25)
            player->y++;
            break;

        case 'a': 
            if (player->y < 17 || player->y > 30 || player->x > 58 || player->x < 37)
            player->x--;
            break;

        case 'd':
            if (player->y < 17 || player->y > 30 || player->x < 33 || player->x > 55)
            player->x++;
            break;
        case 'l':
            player->dir = 1;
            break;
        case 'j':
            player->dir = 0;
            break;
        default:
            break;
    }


    return 0;
}

int player_draw(int rank, char keypress, struct Player * player){
    mvprintw(player->y - 1, player->x - 1, "___");
    if (keypress == 'a'){
        mvprintw(player->y, player->x - 1, "[O|");
    } else {
        mvprintw(player->y, player->x - 1, "|O]");
    }
    mvprintw(player->y + 1, player->x, "+");
    attron(COLOR_PAIR(5));
    if (player->dir == 1){
        printw("-|==");
    } else {
        mvprintw(player->y + 1, player->x - 4, "==|-");
    }
    attron(COLOR_PAIR(1));
    mvprintw(player->y + 2, player->x, "^");
    mvprintw(2, 0, "rank: %d", rank);

    return 0;    
}

#include "ai.h"

struct Enemy * enemy_new(int x, int y){
    struct Enemy * enemy;
    enemy = calloc(1, sizeof(struct Enemy));
    enemy->x = x;
    enemy->y = y;
    enemy->alive = 1;
    enemy->dir = 0;
    enemy->cycle = 0;
    return enemy;
}

int update_enemy(struct Enemy * enemy, struct Player * player, int player_lives, int speed){
    if (enemy == NULL){
        return 11;
    }
    (void)speed;
    if (enemy->alive == 1){
        mvprintw(enemy->y, enemy->x, "    ");
        mvprintw(enemy->y + 1, enemy->x, "    ");
        mvprintw(enemy->y + 2, enemy->x, "    ");
        if (enemy->y < player->y + 15 && enemy->x < player->x + 37 && enemy->y > player->y - 15 && enemy->x > player->x - 37){     
            if (speed == 1){
                if (enemy->y < player->y){
                    enemy->y++;
                }else if (enemy->y > player->y){
                    enemy->y--;
                }else if (enemy->x < player->x){
                    enemy->x++;
                }else if (enemy->x > player->x){
                    enemy->x--;
                }
            }else{
                if (enemy->y < player->y){
                    enemy->y++;
                }else if (enemy->y > player->y){
                    enemy->y--;
                }else if (enemy->x < player->x){
                    enemy->x+=2;
                }else if (enemy->x > player->x){
                    enemy->x-=2;
                }
            }
        }else{
            if (enemy->cycle == 3){
                enemy->dir = (int)rand() % 4;
                enemy->cycle = 0;
            }
            enemy->cycle++;
            switch (enemy->dir){
                case 0:
                enemy->y++;
                break;
                case 1:
                enemy->y--;
                break;
                case 2:
                enemy->x++;
                break;
                case 3:
                enemy->x--;
                break;
                default:
                break;
            }
        }
        if (enemy->x < player->x + 5 && player->y + 1 > enemy->y && enemy->y + 2 > player->y && enemy->x > player->x - 1){
            enemy->alive = 0;
            if (player->dir == 1){
                return 2;
            }else{
                return 1;
            }
        }
        if (enemy->x > player->x - 5 && player->y + 1 > enemy->y && enemy->y + 2 > player->y && player_lives > 0 && enemy->x < player->x + 1){
            player_lives--;
            enemy->alive = 0;
            if (player->dir == 1){
                return 1;
            }else{
                return 2;
            }
        }  
    }
    return 0;
}

int draw_enemy(struct Enemy * enemy){
    attron(COLOR_PAIR(2));
    if (enemy->alive == 1){
        mvprintw(enemy->y, enemy->x, "{^^}");
        mvprintw(enemy->y + 1, enemy->x, "/||\\");
        mvprintw(enemy->y + 2, enemy->x, "/  \\");
    }
    refresh();
    attron(COLOR_PAIR(1));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "ai.h"
#include "player.h"
#include "menu.h"

short COLOR_GREY = 8;

int draw_crash_site(void);
int set_colors(void);


int main(void) {
    clear_screen();
    initscr();
     start_color();
    curs_set(0);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_YELLOW, 750, 500, 0);
    init_color(COLOR_GREEN, 0, 750, 0);
    init_color(COLOR_GREY, 500, 500, 500);
    init_pair(1, COLOR_WHITE, COLOR_YELLOW);
    init_pair(2, COLOR_RED, COLOR_YELLOW);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_GREY);
    init_pair(5, COLOR_GREY, COLOR_YELLOW);
    init_pair(6, COLOR_RED, COLOR_RED);
    int i = 0;

    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(6));
    mvprintw(35, 0, "|________________________________________________________________________________________________________|"); 
    move(0, 105);
    for(i = 0; i < 35; i++){
        mvprintw(i, 105, "|");
    }
    attron(COLOR_PAIR(1));
    srand((unsigned)time(NULL));
    noecho();
    int running = 1;
    char keypress;
    int rank = 1;
    int iteration = 0;
    int tenit = 0;
    int level = 0;
    int enemies = 5;
    move(0, 0);
    for(i = 0; i < 3; i++){
        printw("|] ");
    }
    draw_crash_site();

    struct Player * player;
    player = player_new(rank, 15, 17);
    struct Enemy * enemy[150] = {NULL, NULL};
    for (i = 0; i < 5; i++){
        enemy[i] = enemy_new(rand() % 40 + 5, rand() % 20 + 2);
    }
    int lives = 10;
    int score = 0;
    int dead = 0;
    int moves = 0;

    int returned = 0;
    player_draw(rank, 'c', player);
    draw_enemy(enemy[0]);
    run_menu();

    clear_screen();
    player_draw(rank, 'c', player);
    draw_enemy(enemy[0]);
    draw_crash_site();

    attron(COLOR_PAIR(6));
    mvprintw(35, 0, "|_____________________________________________________________________________________________________________|");
    for(i = 0; i < 35; i++){
        mvprintw(i, 110, "|");
    }

    while(running == 1){

        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "                                                                                        ");
        mvprintw(1, 0, "score: ");
        printw("%d", score);
        moves++;

        move(0, 0);
        
        i = 0;
        while(i < lives){
            printw("|]");
            i++;
        }
        printw("    %d", lives);

        mvprintw(3, 0, "enemies: %d", enemies);

        build_level(rank);

        printw("\n");
        move(0, 50);
        refresh();
        
        keypress = (char)getch();
        if (keypress == 'b'){
            enemy[enemies] = enemy_new(rand() % 40 + 5, rand() % 20 + 2);
            enemies++;
            score -= 10;
            if (rank < 10){
                rank--;
                lives = 3 * rank;
            } else {
                rank -= 3;
                lives = 30;
            }
        }
        
        if (keypress == 'm'){
            attron(COLOR_PAIR(1));
            clear_screen();
            dead = 0;
            main();
        }

        if (keypress == 'q'){
            mvprintw(13, 15, "do you really want to quit?");
            mvprintw(15, 9, "press any key to quit or c to continue");
            refresh();
            if (getch() != 'c'){
                curs_set(1);
                endwin();
                break;
            }
            
            mvprintw(13, 15, "                           ");
            mvprintw(15, 9, "                                      ");
        }


        if (player_update(rank, keypress, player)){
            for (i = 0; i < enemies; i++){
                free(enemy[i]);
                enemy[i] = NULL;
            }
            if (player != NULL){
                free(player);
            }
            player = NULL;
            fprintf(stderr, "RUNTIME ERROR: player = NULL and cannot be used");
            return 1; 
        }
        
        if (level == 0){
            mvprintw(5, 0, "destroy 100 robots");
        }

        if (level == 1){
            mvprintw(5, 0, "get 25 hp for later survival");
        }

        if (level == 2){
            mvprintw(5, 0, "have 300 robots destroyed!      ");
        }

        if (level == 3){
            mvprintw(5, 0, "outmaneuver the robots until your ship repair is complete");
        } 

        if (level == 0 && score > 100){
            level = 1;
            lives -= 5;
        } 

        if (level == 1 && lives > 25){
            level = 2;
            lives -= 5;
        }

        if (level == 2 && score > 300){
            level++;
            //spawn_boss
        }

        if (level == 3 && moves > 1750){
            show_ending(score, rank);
            while(1){
                keypress = (char)getch();
                if (keypress == 'm'){
                    main();
                    break;
                }
            }
        }

        player_draw(rank, keypress, player);
        for (i = 0; i < enemies; i++) {
            if (level < 3){
                returned = update_enemy(enemy[i], player, lives, 1);
            }else{
                returned = update_enemy(enemy[i], player, lives, 2);
            }
            if (returned == 1){
                if (rank < 38){
                    lives--;
                }else if (rand() % 4 > 0){
                    lives -= 3;
                }else{
                    lives--;
                }
            }else if (returned == 2){
                score++;
                if (score > rank * 10){
                    rank++;
                    if (lives < 50){
                        lives += 2;
                    }
                    if (enemies < 45){
                        enemy[enemies] = enemy_new(rand() % 40 + 5, rand() % 20 + 2);
                        enemies++;
                    }
                }
            }else if (returned == 11){
                free(player);
                fprintf(stderr, "RUNTIME ERROR: enemy %d = NULL and cannot be used", i);
                return 1; 
            }
            draw_enemy(enemy[i]);
        }
        if (lives < 1){
            attron(COLOR_PAIR(3));
            clear_screen();
            dead = 1;
            running = 0;
            break;
        }
        iteration++;
        if (iteration == 10){
            if (lives < 10 + rank && tenit == 2) {
                lives++;
                tenit = 0;
            }
            attron(COLOR_PAIR(6));
            mvprintw(35, 0, "|_____________________________________________________________________________________________________________|");
            for(i = 0; i < 35; i++){
                mvprintw(i, 110, "|");
            }
            attron(COLOR_PAIR(1));
            tenit++;
            for(i = 0; i < enemies; i++){
                if(enemy[i]->alive == 0){
                    enemy[i]->alive++;
                    enemy[i]->x = rand() % 100 + 5;
                    enemy[i]->y = rand() % 15 + 2;
                }
            }
            draw_crash_site();
            iteration = 0;
        }
    }
    if (dead == 1){
        while(1){
            show_grave();
            keypress = (char)getch();
            if (keypress == 'm'){
                attron(COLOR_PAIR(1));
                clear_screen();
                dead = 0;
                main();
            } else if (keypress == 'q') {
                endwin();
                exit(0);
            }
        }
    }

}

struct Level build_level(int rank){
    struct Level level;
    int j = 0;
    
    level.width = 50 / rank;
    level.height = 50 / rank;

    int i = 0;
    for(i = 1; i < 50 / rank; i++){
        for (j = 1; j < 50 / rank; j++){
            if (rand() * 12 == 1){
                level.map[i][j] = 'o';
            }else{
                level.map[i][j] = ' ';
            }
        }
    }
    return level;
}


int draw_crash_site(void){
    attron(COLOR_PAIR(5));
    mvprintw(20, 40, "oo ooooo  o//ooo ");
    mvprintw(21, 40, "   o||o oo//oo");
    mvprintw(22, 40, "    ||   //   ");
    attron(COLOR_PAIR(1));
    mvprintw(23, 40, "  ____________");
    attron(COLOR_PAIR(4));
    mvprintw(24, 40, " /|_|  |_|_/_ |<");
    mvprintw(25, 40, "/ |_|  |_| /| |{");
    mvprintw(26, 40, "|         / / |{");
    mvprintw(27, 40, "/-|/-/|- /-| /|-");
    mvprintw(28, 40, "<> o ~--->");
    attron(COLOR_PAIR(1));
    return 0;
}
int clear_screen(void){
    int i = 0;
    int j = 0;
    for (i = 0; i < 200; i++){
        for (j = 0; j < 100; j++){
            mvprintw(j, i, " ");
        }
    }
    return 0;
}
int show_grave(void){
    attron(COLOR_PAIR(4));
    mvprintw(10, 40, " _________");
    mvprintw(11, 40, "/  R.I.P  \\");
    mvprintw(12, 40, "| player  |");
    mvprintw(13, 40, "|killed by|");
    mvprintw(14, 40, "|  robot  |");
    mvprintw(15, 40, "|_________|");
    mvprintw(18, 18, "press q to quit or the m to go to the main menu");

    return 0;
}

int set_colors(void){
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_YELLOW, 1000, 500, 0);
    init_color(COLOR_GREEN, 0, 750, 0);
    init_color(COLOR_GREY, 500, 500, 500);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_GREY);
    init_pair(4, COLOR_GREY, COLOR_WHITE);
    return 0;
}

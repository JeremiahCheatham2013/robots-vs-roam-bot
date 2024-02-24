#include "menu.h"
#include <stdlib.h>

void run_menu(void){
    int i = 0;
    int selected = 0;
    draw_bg();
    draw_menu(0);
    char keypress = 'v';
    while(1){
        keypress = (char)getch();
        attron(COLOR_PAIR(6));
    mvprintw(35, 0, "|________________________________________________________________________________________________________|");
        for(i = 0; i < 35; i++){
            mvprintw(i, 105, "|");
        }
        if (keypress == 's' && selected < 1){
            selected++; 
        }else if (keypress == 'w' && selected > 0){
            selected--;
        }else if (keypress == 'a'){
            attron(COLOR_PAIR(1));
            do_menu_thing(selected);
            break;
        }
        draw_menu(selected);
    }

}

void show_ending(int score, int rank){
    attron(COLOR_PAIR(4));
    mvprintw(15, 0, "               rank: %d           \\  /   __   |  |       |      |  -|- |\\  |   |        score: %d           |", rank, score);
    mvprintw(16, 0, "                                   \\/   /  \\  |  |       |      |   |  | \\ |   |                             |");
    mvprintw(17, 0, "                                   ||   |  |  |  |       \\  /\\  /   |  |  \\|   |                             |");
    mvprintw(18, 0, "                                   ||   \\__/  \\__/        \\/  \\/   _|_ |   |   o                             |");
    mvprintw(19, 49, "press M to go to main menu");
}

void draw_menu(int selected){
    attron(COLOR_PAIR(4));
    mvprintw(13, 35, "|START|");
    attron(COLOR_PAIR(1));
    printw("            ");

    attron(COLOR_PAIR(4));
    mvprintw(17, 35, "|EXIT|");
    attron(COLOR_PAIR(1));
    printw("            ");

    attron(COLOR_PAIR(4));

    if (selected == 0){
        mvprintw(13, 43, "PRESS 'A'");
    } else if (selected == 1) {
        mvprintw(17, 43, "PRESS 'A'"); 
    }
}

void draw_bg(void){
    attron(COLOR_PAIR(4));
    mvprintw(4, 17, "___________________________________________________________________________");
    mvprintw(5, 17, "|| \\ / \\ | \\ / \\ -|- /    \\    / /     | \\ / \\  /\\  |--|--|    | \\ / \\ -|-|");
    mvprintw(6, 17, "||_| | | |-- | |  |  --    \\  /  --    |_| | | /__\\ |  |  | -- |-- | |  | |");
    mvprintw(7, 17, "|| \\ \\_/ |_/ \\_/  |  _/     \\/   _/    | \\ \\_/ |  | |  |  |    |_/ \\_/  | |");
    mvprintw(8, 17, "|_________________________________________________________________________|");
    mvprintw(24, 0, "         controls:            ");
    mvprintw(25, 0, "select option (main menu) = WS");
    mvprintw(26, 0, "movement (in game) = WASD     ");
    mvprintw(27, 0, "regain lives(high-rank) = B   ");
    mvprintw(28, 0, "quit(while playing) = Q       ");
    mvprintw(29, 0, "set sword right = L           ");
    mvprintw(30, 0, "set sword left = J            ");
    mvprintw(31, 0, "resize = ctrl +/-             ");
    mvprintw(32, 0, "go to main-menu (in game) = m ");
    mvprintw(30, 35, "  your goal is to survive and destroy 300 robots");
    mvprintw(31, 35, "and collect their remains to start your ship repair");
    mvprintw(32, 35, "        whilst still surviving robots.");
    attron(COLOR_PAIR(2));
    mvprintw(2, 32, "MAKE SURE YOU SEE THE BOTTOM AND RIGHT RED BORDER!");
}

void do_menu_thing(int selected){
    if (selected == 1){
        endwin();
        exit(0);
    } 
}

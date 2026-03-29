#include <stdlib.h>
#include <curses.h>
#include "menu.h"

using namespace std;

int main(int argc, char **argv){
    initscr();
    noecho();
    curs_set(0);

    if(!has_colors())
    {
        return -1;
    }

    start_color();
    init_pair(1, COLOR_WHITE,COLOR_BLUE);

    int term_yMax,term_xMax;
    getmaxyx(stdscr,term_yMax,term_xMax);

    WINDOW *main_win = newwin(term_yMax-1,term_xMax-1,1,1);
    box(main_win,0,0);

    string File_Menu[] = {"Connect","Disconnect","Exit"};
    string View_Menu[] = {"Info","Machines","Log"};

    Menu main_menus[2] = {
        Menu("File",'f',File_Menu,3),
        Menu("View",'v',View_Menu,3),
    };

    MenuBar main_menubar = MenuBar(main_win,main_menus,2);
    main_menubar.draw();

    keypad(main_win, TRUE);
    int main_menus_input;
    while((main_menus_input = wgetch(main_win))){
        if(main_menus_input <= 255)
        {
            main_menubar.handleTrigger(main_menus_input);
            main_menubar.draw();
        }
        else if(main_menus_input == KEY_RESIZE)
        {
            clear();
            refresh();
            delwin(main_win);
            getmaxyx(stdscr,term_yMax,term_xMax);
            main_win = newwin(term_yMax-1,term_xMax-1,1,1);
            box(main_win,0,0);
            main_menubar.resize(main_win);
            main_menubar.draw();
            wrefresh(main_win);
        }
    }

    endwin();
    return 0;
}

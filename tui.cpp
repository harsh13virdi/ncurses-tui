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

    int yMax,xMax;
    getmaxyx(stdscr,yMax,xMax);

    WINDOW *win = newwin(yMax-1,xMax-1,yMax-yMax+1,xMax-xMax+1);
    box(win,0,0);

    string menu1[] = {"New","Open","Save","Exit"};
    string menu2[] = {"Copy","Cut","Paste"};
    string menu3[] = {"Sidebar","Terminal"};

    Menu menus[3] = {
        Menu("File",'f',menu1,4),
        Menu("Edit",'e',menu2,3),
        Menu("View",'v',menu3,2),
    };

    MenuBar menubar = MenuBar(win,menus,3);
    menubar.draw();

    char ch;
    while((ch = wgetch(win))){
        menubar.handleTrigger(ch);
        menubar.draw();
    }

    endwin();
    return 0;
}



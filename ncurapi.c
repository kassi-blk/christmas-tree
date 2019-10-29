#include "ncurapi.h"

void
pos_set(int x, int y) {
    move(y, x);
}

void
sym_set(char sym, int x, int y) {
    pos_set(x, y);
    printw("%c", sym);
}

bool
colors_check(void) {
    if (!has_colors()) {
        printw("Sorry, but your terminal don't support the colors!\n");
        printw("But nothing wrong. ");
        printw("Just enjoy within one-color animation. :)");
        getch();
        erase();

        return false;
    }

    return true;
}

void
color_on(int index) {
    attron(COLOR_PAIR(index));
}

void
color_off(int index) {
    attroff(COLOR_PAIR(index));
}

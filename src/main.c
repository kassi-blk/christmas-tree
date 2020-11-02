#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "tree.h"

static void deinit(void);
static void show_help(void);

int main(int argc, char *argv[])
{
    int x;
    int y;
    char c;
    int k;
    bool garland = true;
    bool rinit = false;
    int xm;
    int ym;
    struct tree *tree = NULL;

    if (argc == 2 && !strcmp(argv[1], "--help")) {
        show_help();

        return -1;
    }
    else
        rinit = argc == 2
            && (!strcmp(argv[1], "--rand") || !strcmp(argv[1], "-r"));

    if (argc != 6 && !rinit) {
        show_help();

        return -1;
    }

    if (!rinit) {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
        c = argv[3][0];

        k = atoi(argv[4]);
        if (k < 1) {
            printf("A 'k' must be greater than a zero.\n");

            return -1;
        }

        if (!strcmp(argv[5], "true") || argv[5][0] == '1')
            garland = true;
        else if (!strcmp(argv[5], "false") || argv[5][0] == '0')
            garland = false;

        tree = malloc(sizeof(struct tree));
        tree->x = x;
        tree->y = y;
        tree->c = c;
        tree->k = k;
        tree->garland = garland;
    }

    srand(time(NULL));

    /* Curse the program. */
    initscr();
    curs_set(0);
    nodelay(stdscr, true);
    noecho();

    xm = getmaxx(stdscr);
    ym = getmaxy(stdscr);
    if (x > xm - 1 || y > ym - 1) {
        printw("An 'x' or 'y' is too high for the your screen.\n");

        deinit();
    }
    else if (x < 0 || y < 0) {
        printw("An 'x' and 'y' must be greater than a zero.\n");

        deinit();
    }

    if (has_colors()) {
        start_color();

        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(2));
    }
    else {
        printw("The your terminal isn't supports the colors.\n");
        getch();
        erase();
    }

    tree = tree_init(tree, xm, ym);
    tree_draw(tree);

    if (garland) {
        /* TODO: Use a timer. */
        while (getch() != 'q') {
            garland_draw(tree);

            refresh();
            usleep(500000);
        }
    }

    curs_set(2);
    nodelay(stdscr, false);
    echo();
    endwin();

    free(tree);

    return 0;
}

static void
deinit(void)
{
    curs_set(2);
    nodelay(stdscr, false);
    echo();
    getch();
    endwin();
    exit(-1);
}

static void
show_help(void)
{
    printf(
        "The positional arguments (in the appropriate order):\n"
        "  x          a tree's position by x                 \n"
        "  y          a tree's position by y                 \n"
        "  c          a tree's symbol                        \n"
        "  k          a tree's compress coefficient          \n"
        "  garland    a garland's visibility (bool)          \n"
        "                                                    \n"
        "The flags:                                          \n"
        "  -r, --rand    generate a random tree              \n");
}

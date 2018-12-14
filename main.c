#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <time.h>

#include <ncurses.h>

#include "ncurapi.h"

int main(void) {
	srand(time(NULL));

	struct tree *tre = NULL;

	initscr();
	curs_set(0);

	if (colors_check()) {
		colors_support = true;
		start_color();
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_CYAN, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_RED, COLOR_BLACK);
		color_on(2);
	} else
		colors_support = false;

	tre = tree_init_rand(tre);

	while (1) {	
		tree_draw(tre);
		refresh();
		usleep(500000);
	}

	getch();
	curs_set(2);
	endwin();

	free(tre);

	return 0;
}

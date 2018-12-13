#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>

#include <ncurses.h>

#include "ncurapi.h"

int main(void) {
	srand(time(NULL));

	struct tree *tre = NULL;

	initscr();
	curs_set(0);

	tre = tree_init_rand(tre);
	tree_draw(tre);

	getch();
	curs_set(2);
	endwin();

	free(tre);

	return 0;
}

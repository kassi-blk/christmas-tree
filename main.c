#include <stdio.h>
#include <stdbool.h>

#include <ncurses.h>

#include "ncurapi.h"

int main(void) {
	struct triangle tr = {
		.x = 40,
		.y = 5,
		.sym = '@',
		.k = 2,
		.size = 10,
		.base = false
	};

	initscr();
	curs_set(0);

	draw_triangle(&tr);

	getch();
	curs_set(2);
	endwin();

	return 0;
}

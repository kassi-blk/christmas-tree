#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <time.h>

#include <ncurses.h>

#include "ncurapi.h"

int main(int argc, char *argv[]) {
	bool rand_init;
	bool garland;

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("usage: ./prog <x> <y> <sym> <k> <garland>  \n");
		printf("x       - tree pos x                       \n");
		printf("y       - tree pos y                       \n");
		printf("sym     - tree sym                         \n");
		printf("k       - tree compress coefficient        \n");
		printf("garland - show garland (true/false)        \n");
		printf("-------------------------------------------\n");
		printf("also you can use flags without arguments:  \n");
		printf("    -r, --rand                 random tree \n");
		printf("-------------------------------------------\n");
		printf("about k:                                   \n");
		printf("(0)      #     k = 1  |    #     k = 2     \n");
		printf("(1)     # #           |   # #              \n");
		printf("(2)    #   #          |   # #              \n");
		printf("(3)   #     #         |  #   #             \n");
		printf("(4)  #########        |  #####             \n");

		return 0;
	} else {
		if ((argc == 2 && strcmp(argv[1], "--rand") == 0) ||
			(argc == 2 && strcmp(argv[1], "-r") == 0)) {
			rand_init = true;

			/* yes... */
			argv[1] = " ";
			argv[2] = " ";
			argv[3] = " ";
			argv[4] = " ";
			argv[5] = " ";
		} else
			rand_init = false;
	}

	if (argc != 6 && !rand_init) {
		printf("type --help for more information\n");

		return 1;
	}

	char *px;
	char *py;
	char *pk;

	long int x = strtol(argv[1], &px, 10);
	long int y = strtol(argv[2], &py, 10);
	char sym = argv[3][0];
	long int k = strtol(argv[4], &pk, 10);

	if (!rand_init) {
		if (*px != '\0' || *py != '\0' || *pk != '\0') {
			printf("strange arguments...\n");

			return 1;
		}

		if (strcmp(argv[5], "true") == 0 ||
			argv[5][0] == '1')
			garland = true;
		else if (strcmp(argv[5], "false") == 0 ||
			argv[5][0] == '0')
			garland = false;
		else
			garland = true;

		if (k < 1) {
			printf("k must be greater than 0\n");

			return 1;
		}
	}

	struct tree *tre;

	if (rand_init)
		tre = NULL;
	else {
		tre = malloc(sizeof(struct tree));

		tre->x = x;
		tre->y = y;
		tre->sym = sym;
		tre->k = k;
		tre->garland = garland;
	}

	srand(time(NULL));

	initscr();
	curs_set(0);

	int max_x = getmaxx(stdscr);
	int max_y = getmaxy(stdscr);

	if (x > (max_x - 1) || y > (max_y - 1)) {
		printw("either 'x' (%3d) > your_screen_width  (%3d) or\n", x, max_x);
		printw("       'y' (%3d) > your_screen_height (%3d)\n", y, max_y);
		goto failure_exit;
	} else if (x < 0 || y < 0) {
		printw("x and y must be greater than 0\n");
		goto failure_exit;
	}

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

	tre = tree_init(tre);

	while (1) {
		tree_draw(tre);
		refresh();
		usleep(500000);
	}

failure_exit:
	getch();
	curs_set(2);
	endwin();

	free(tre);

	return 0;
}

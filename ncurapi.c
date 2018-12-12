#include "ncurapi.h"

void set_pos(int x, int y) {
	move(y, x);
}

void set_sym(int x, int y, char sym) {
	set_pos(x, y);
	printw("%c", sym);
}

void draw_triangle(struct triangle *tr) {
	int k = 0;

	int i;
	for (i = 0; i < tr->size; i++) {
		set_sym(tr->x - k, tr->y + i, tr->sym);
		set_sym(tr->x + k, tr->y + i, tr->sym);

		if (i % tr->k == 0)
			k++;
	}

	if (tr->base) {
		/* draw triangle base */
		int j;
		for (j = (-k + 1); j < k; j++)
			set_sym(tr->x + j, tr->y + (i - 1), tr->sym);
	}
}

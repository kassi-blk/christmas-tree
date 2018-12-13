#include "ncurapi.h"

void pos_set(int x, int y) {
	move(y, x);
}

void sym_set(char sym, int x, int y) {
	pos_set(x, y);
	printw("%c", sym);
}

struct tree * tree_init_rand(struct tree *tre) {
	int max_x;
	int max_y;

	int x;
	int y;
	int size;
	char sym;
	int count;

	char syms[10] = {'!', '@', '#', '$', '%', '&', '0', '3', '5', '8'};

	max_x = getmaxx(stdscr);
	max_y = getmaxy(stdscr);
	sym = syms[random(0, 9)];
	size = random(TREE_TIP_SIZE_MIN, TREE_TIP_SIZE_MAX);
	count = random(TREE_PARTS_MIN, TREE_PARTS_MAX);

	x = random(size * count + count, max_x - size * count - count);
	y = 2;

	tre = malloc(sizeof(struct tree));
	tre->tr = malloc(sizeof(struct triangle) * count);

	int i;
	for (i = 0; i < count; i++) {
		tre->tr[i].x = x;
		tre->tr[i].sym = sym;
		tre->tr[i].k = 1;
		tre->tr[i].size = size + (i > 0 ? (tre->tr[i - 1].size + 1) : 0);
		tre->tr[i].y = y + (i > 0 ? (tre->tr[i - 1].y + 1) : 0);
		tre->tr[i].base = true;
	}

	tre->count = count;

	return tre;
}

void triangle_draw(struct triangle *tr) {
	int k = 0;

	int i;
	for (i = 0; i < tr->size; i++) {
		sym_set(tr->sym, tr->x - k, tr->y + i);
		sym_set(tr->sym, tr->x + k, tr->y + i);

		if (i % tr->k == 0)
			k++;
	}

	if (tr->base) {
		/* draw triangle base */
		int j;
		for (j = (-k + 1); j < k; j++)
			sym_set(tr->sym, tr->x + j, tr->y + (i - 1));
	}
}

void tree_draw(struct tree *tre) {
	int i;
	for (i = 0; i < tre->count; i++)
		triangle_draw(&tre->tr[i]);
}

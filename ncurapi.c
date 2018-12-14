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

struct tree * 
tree_init_rand(struct tree *tre) {
	tre = malloc(sizeof(struct tree));

	int max_x = getmaxx(stdscr);
	/* int max_y = getmaxy(stdscr); */
	char sym = random(33, 96);
	int size = random(TREE_TIP_SIZE_MIN, TREE_TIP_SIZE_MAX);
	int count = random(TREE_PARTS_MIN, TREE_PARTS_MAX);

	int x = random(count * 5 + 1, max_x - (count * 5 + 1));
	int y = 2;
	
	tre->tr = malloc(sizeof(struct triangle) * count);

	int i;

	for (i = 0; i < count; i++) {
		tre->tr[i].x = x;
		tre->tr[i].y = (i > 0 ? (tre->tr[i - 1].y + 
			tre->tr[i - 1].y / 2 + 1) : y);
		tre->tr[i].sym = sym;
		tre->tr[i].k = 1;
		tre->tr[i].size = size += 5;	
		tre->tr[i].base = true;
		tre->tr[i].fill = true;
		tre->tr[i].garland = true;
	}

	tre->count = count;

	/* trunk */
	tre->tru = malloc(sizeof(struct trunk));

	tre->tru->x = tre->tr[count - 1].x;
	tre->tru->y = tre->tr[count - 1].y + tre->tr[count - 1].size;
	tre->tru->sym = random(33, 96);
	tre->tru->thickness = random(1, tre->tr[count - 1].size / 2);
	tre->tru->height = random(TRUNK_HEIGHT_MIN, TRUNK_HEIGHT_MAX);

	return tre;
}

void 
triangle_draw(struct triangle *tr) {
	int k = 0;
	int i;
	int j;

	for (i = 0; i < tr->size; i++) {
		if (colors_support)
			color_on(1);

		sym_set(tr->sym, tr->x - k, tr->y + i);
		sym_set(tr->sym, tr->x + k, tr->y + i);

		if (tr->fill) { /* fill triangle */
			for (j = (-k + 1); j < k; j++)
				sym_set(tr->sym, tr->x + j, tr->y + i);
		}

		if (i % tr->k == 0)
			k++;
	}

	if (tr->base) { /* draw triangle base */
		for (j = (-k + 1); j < k; j++)
			sym_set(tr->sym, tr->x + j, tr->y + (i - 1));
	}

	if (colors_support)
		color_on(2);
}

void
trunk_draw(struct trunk *tru, int k) {
	int trunk_thickness_reduced = tru->thickness / k;
	int trunk_half = trunk_thickness_reduced / 2;
	int i;
	int j;

	for (i = 0; i < tru->height; i++) {
		if (colors_support)
			color_on(3);

		for (j = -trunk_half; j < trunk_half + 1; j++)
			sym_set(tru->sym, tru->x + j, tru->y + i);
	}

	if (colors_support)
		color_on(2);
}

void
garland_draw(struct triangle *tr, char sym) {
	int k = tr->size / tr->k - (GARLAND_DECLINE - 1) + 
		(tr->k > 1 ? tr->k - 1 : 0);
	int i = tr->size;
	int j;
	
	/* "hang" garland on triangle */
	for (j = (-k + 1) + 1; j < k - 1; j++) {
		if (colors_support)
			color_on(random(3, 7));

		if (j == (-k + 1) + 1 || j == (k - 1) - 1) 
			sym_set(sym, tr->x + j, tr->y + 
				(i - GARLAND_DECLINE - 1));
		else
			sym_set(sym, tr->x + j, tr->y + 
				(i - GARLAND_DECLINE));
	}

	if (colors_support)
		color_on(2);
}

void
tree_draw(struct tree *tre) {
	int i;

	for (i = 0; i < tre->count; i++)
		triangle_draw(&tre->tr[i]);

	/* draw garland here because otherwise it will be erased by triangles */
	for (i = 0; i < tre->count; i++) {
		if (tre->tr[i].garland)
			garland_draw(&tre->tr[i], GARLAND_SYM);
	}

	trunk_draw(tre->tru, tre->tr[0].k);
}

bool 
colors_check(void) {
	if (!has_colors()) {
		printw("Sorry, but your terminal don't support the colors!\n");
		printw("But nothing wrong. "); 
		printw("Just enjoy within one-color animation. :)");
		getch();

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

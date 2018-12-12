#ifndef NCURAPIH
#define NCURAPIH

#include <stdbool.h>

#include <ncurses.h>

struct triangle {
	int x;
	int y;
	char sym;
	int k; /* compress coefficient */
	int size;
	bool base;
};

void set_pos(int x, int y);
void set_sym(int x, int y, char sym);
void draw_triangle(struct triangle *tr);

#endif

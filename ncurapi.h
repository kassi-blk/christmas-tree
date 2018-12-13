#ifndef NCURAPIH
#define NCURAPIH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>

#include <ncurses.h>

#define random(min, max) (min + rand() % (max - min + 1))

#define TREE_TIP_SIZE_MIN 3
#define TREE_TIP_SIZE_MAX 9
#define TREE_PARTS_MIN 2
#define TREE_PARTS_MAX 5

struct triangle {
	int x;
	int y;
	char sym;
	int k; /* compress coefficient */
	int size;
	bool base;
};

struct tree {
	int x;
	int y;
	char sym;
	struct triangle *tr;
	int count;
};

void 					pos_set(int x, int y);
void 					sym_set(char sym, int x, int y);
struct tree * tree_init_rand(struct tree *tre);
void 					triangle_draw(struct triangle *tr);
void 					tree_draw(struct tree *tre);

#endif

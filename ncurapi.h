#ifndef NCURAPIH
#define NCURAPIH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>

#include <ncurses.h>

#define random(min, max) (min + rand() % (max - min + 1))

#define TRUNK_HEIGHT_MIN 2
#define TRUNK_HEIGHT_MAX 4

#define GARLAND_DECLINE 2
#define GARLAND_SYM 'O'

#define TREE_TIP_SIZE_MIN 3
#define TREE_TIP_SIZE_MAX 5
#define TREE_PARTS_MIN 2
#define TREE_PARTS_MAX 6
#define TREE_PARTS_SIZE_OFFSET 5

struct triangle {
	int x;
	int y;
	char sym;
	int k; /* compress coefficient (i don't know what for it may be used  :\ ) */
	int size;
	bool base;
	bool fill;
	bool garland;
	struct toy *ty;
};

struct trunk {
	int x;
	int y;
	char sym;
	int thickness;
	int height;
};

struct tree {
	int x;
	int y;
	char sym;
	int k;
	int count;
	struct triangle *tr;
	struct trunk *tru;
};

void          pos_set(int x, int y);
void          sym_set(char sym, int x, int y);
struct tree * tree_init(struct tree *tre, int x, int y, char sym, int k);
struct tree * tree_init_rand(struct tree *tre);
void          triangle_draw(struct triangle *tr);
void          trunk_draw(struct trunk *tru, int k);
void          garland_draw(struct triangle *tr, char sym);
void          tree_draw(struct tree *tre);
bool          colors_check(void);
void          color_on(int index);
void          color_off(int index);

bool colors_support;

#endif /* NCURAPIH */

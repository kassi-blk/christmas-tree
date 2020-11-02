#ifndef TREE_H
#define TREE_H

#include <ncurses.h>
#include <math.h>
#include <stdlib.h>

#define TREE_K_MIN 1
#define TREE_K_MAX 4
#define TREE_TIP_SIZE_MIN 3
#define TREE_TIP_SIZE_MAX 5
#define TREE_PARTS_MIN 1
#define TREE_PARTS_MAX 6
#define TREE_PARTS_SIZE_OFFSET 5
#define TRUNK_HEIGHT_MIN 2
#define TRUNK_HEIGHT_MAX 4
#define GARLAND_RISE 2
#define GARLAND_SYM 'O'

#define random(min, max) (min + rand() % (max - min + 1))

struct triangle {
    int x;
    int y;
    char c;
    int h;
    bool base;
    bool fill;
    int *line;
};

struct trunk {
    int x;
    int y;
    char c;
    int thickness;
    int h;
};

struct tree {
    int x;
    int y;
    char c;
    int k; /* A compress coefficient. */
    int cnt;
    bool garland;
    struct triangle *tr;
    struct trunk *trunk;
};

struct tree * tree_init(struct tree *t, int xm, int ym);
void tree_draw(const struct tree *t);
void triangle_draw(const struct triangle *tr, int k);
void trunk_draw(const struct trunk *trunk, int k);
void garland_draw(const struct tree *t);

#endif /* TREE_H */

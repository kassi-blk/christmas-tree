#ifndef TREE_H
#define TREE_H

#include <ncurses.h>

#include "ncurapi.h"

#define TREE_K_MIN 1
#define TREE_K_MAX 4

struct tree * tree_init(struct tree *tre);
void triangle_draw(struct triangle *tr);
void trunk_draw(struct trunk *tru, int k);
void garland_draw(struct triangle *tr, char sym);
void tree_draw(struct tree *tre);

#endif /* TREE_H */

#include "tree.h"

struct tree *
tree_init(struct tree *tre) {
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    int size = random(TREE_TIP_SIZE_MIN, TREE_TIP_SIZE_MAX);
    int count = random(TREE_PARTS_MIN, TREE_PARTS_MAX);

    if (tre == NULL) {
        tre = malloc(sizeof(struct tree));

        tre->x = random(count * TREE_PARTS_SIZE_OFFSET * size,
            max_x - (count * TREE_PARTS_SIZE_OFFSET * size));
        tre->y = 2;
        tre->sym = random(33, 96);
        tre->k = random(TREE_K_MIN, TREE_K_MAX);
        tre->garland = true;
    }

    /* triangles */
    tre->tr = malloc(sizeof(struct triangle) * count);

    int i;
    int j;

    for (i = 0; i < count; i++) {
        tre->tr[i].x = tre->x;
        tre->tr[i].y = tre->y += (i > 0 ? tre->tr[i - 1].size / 2 : 0);
        tre->tr[i].sym = tre->sym;
        tre->tr[i].k = tre->k;
        tre->tr[i].size = size += TREE_PARTS_SIZE_OFFSET;
        tre->tr[i].base = true;
        tre->tr[i].fill = true;
        tre->tr[i].line = malloc(sizeof(int) * tre->tr[i].size);

        /* get triangle line size */
        int line_size = 0;

        for (j = 0; j < tre->tr[i].size; j++) {
            tre->tr[i].line[j] = 1 + line_size;

            if (j % tre->tr[i].k == 0)
                line_size += 2;
        }

        /* check if (triangle.x + triangle.size)              > max_x,
         * check if (triangle.x - triangle.size)              > 0,
         * check if (triangle.y + triangle.size / triangle.k) > max_y */
        if (tre->tr[i].x + tre->tr[i].size / tre->tr[i].k > (max_x - 1) ||
                tre->tr[i].x - tre->tr[i].size < 0 ||
                tre->tr[i].y + tre->tr[i].size > (max_y - 1))
            break;
    }

    tre->count = i;

    /* trunk */
    tre->tru = malloc(sizeof(struct trunk));

trunk_set:
    tre->tru->x = tre->tr[tre->count - 1].x;
    tre->tru->y = tre->tr[tre->count - 1].y + tre->tr[tre->count - 1].size;
    tre->tru->sym = random(33, 96);
    tre->tru->thickness = random(2, tre->tr[tre->count - 1].size / 2);
    tre->tru->height = random(TRUNK_HEIGHT_MIN, TRUNK_HEIGHT_MAX);

    /* check if (triangle.x + triangle.size.x)                > max_x,
     * check if (triangle.y + triangle.size.y + trunk_height) > max_y */
    while ((tre->tr[tre->count - 1].x +
            tre->tr[tre->count - 1].size > (max_x - 1)) ||
            (tre->tr[tre->count - 1].y + tre->tr[tre->count - 1].size +
            tre->tru->height > (max_y - 1))) {
        tre->count--;

        goto trunk_set;
    }

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

        if (tr->fill) { /* fill the triangle */
            for (j = (-k + 1); j < k; j++)
                sym_set(tr->sym, tr->x + j, tr->y + i);
        }

        if (i % tr->k == 0)
            k++;
    }

    if (tr->base) { /* draw the triangle base */
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
    int width = tr->line[(tr->size - 1) - GARLAND_RISE] / 2;
    int i;

    /* hang the garland on the triangle */
    for (i = -width; i < width + 1; i++) {
        color_on(random(3, 7));

        if (i == -width || i == width)
            sym_set(sym, tr->x + i, tr->y + (tr->size - (GARLAND_RISE + 1)));
        else
            sym_set(sym, tr->x + i, tr->y + (tr->size - GARLAND_RISE));
    }

    if (colors_support)
        color_on(2);
}

void
tree_draw(struct tree *tre) {
    int i;

    for (i = 0; i < tre->count; i++)
        triangle_draw(&tre->tr[i]);

    /* draw the garland here, because otherwise it will be erased
     * by another triangles */
    for (i = 0; i < tre->count; i++) {
        if (tre->garland)
            garland_draw(&tre->tr[i], GARLAND_SYM);
    }

    trunk_draw(tre->tru, tre->tr[0].k);
}
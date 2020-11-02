#include "tree.h"

struct tree *
tree_init(struct tree *t, int xm, int ym)
{
    int size = random(TREE_TIP_SIZE_MIN, TREE_TIP_SIZE_MAX);
    int i;
    int j;

    if (!t) {
        t = malloc(sizeof(struct tree));
        t->x = xm / 2;
        t->y = 2;
        t->c = random('!', '`');
        t->k = random(TREE_K_MIN, TREE_K_MAX);
        t->garland = random(0, 1);
    }

    t->cnt = random(TREE_PARTS_MIN, TREE_PARTS_MAX);
    t->tr = malloc(sizeof(struct triangle) * t->cnt);

    /* Setup the triangles. */
    for (i = 0; i < t->cnt; i++) {
        int ll = 0;

        t->tr[i].x = t->x;
        t->tr[i].y = t->y += i > 0 ? t->tr[i - 1].h / 2 : 0;
        t->tr[i].c = t->c;
        t->tr[i].h = size += TREE_PARTS_SIZE_OFFSET;
        t->tr[i].base = true;
        t->tr[i].fill = true;
        t->tr[i].line = malloc(sizeof(int) * t->tr[i].h);

        /* Form the triangle's lines. */
        for (j = 0; j < t->tr[i].h; j++) {
            t->tr[i].line[j] = 1 + ll;

            if (!(j % t->k))
                ll += 2;
        }

        if (t->tr[i].x + t->tr[i].h / t->k > xm - 1
                || t->tr[i].x - t->tr[i].h < 0
                || t->tr[i].y + t->tr[i].h > ym - 1)
            break;
    }

    /* Setup a tree's trunk. */
    t->cnt--;

    t->trunk = malloc(sizeof(struct trunk));
    do {
        int w = t->tr[t->cnt].x + t->tr[t->cnt].h;
        int h = t->tr[t->cnt].y + t->tr[t->cnt].h;

        t->trunk->x = t->tr[t->cnt].x;
        t->trunk->y = t->tr[t->cnt].y + t->tr[t->cnt].h;
        t->trunk->c = random('!', '`');
        t->trunk->thickness = random(2, t->tr[t->cnt].h / 2);
        t->trunk->h = random(TRUNK_HEIGHT_MIN, TRUNK_HEIGHT_MAX);

        if (w > xm - 1 || h > ym - 1 || !h) {
            if (t->cnt > 0)
                /* Not enough space for a tree. Decrease a tree's triangle
                 * count and try again. */
                t->cnt--;

            continue;
        }

        break;
    }
    while (1);

    t->cnt++;

    return t;
}

void
triangle_draw(const struct triangle *tr, int k)
{
    int offset = 0;
    int i;
    int j;

    for (i = 0; i < tr->h; i++) {
        attron(COLOR_PAIR(1));
        mvaddch(tr->y + i, tr->x - offset, tr->c);
        mvaddch(tr->y + i, tr->x + offset, tr->c);

        if (tr->fill) {
            /* Fill a triangle. */
            for (j = -offset + 1; j < offset; j++)
                mvaddch(tr->y + i, tr->x + j, tr->c);
        }

        if (!(i % k))
            offset++;
    }

    if (tr->base) {
        /* Draw a triangle's base. */
        for (j = -offset + 1; j < offset; j++)
            mvaddch(tr->y + i - 1, tr->x + j, tr->c);
    }

    attron(COLOR_PAIR(2));
}

void
trunk_draw(const struct trunk *trunk, int k)
{
    int trunk_thickness_reduced = trunk->thickness / k;
    int trunk_half = trunk_thickness_reduced / 2;
    int i;
    int j;

    for (i = 0; i < trunk->h; i++) {
        attron(COLOR_PAIR(3));

        for (j = -trunk_half; j < trunk_half + 1; j++)
            mvaddch(trunk->y + i, trunk->x + j, trunk->c);
    }

    attron(COLOR_PAIR(2));
}

void
garland_draw(const struct tree *t)
{
    int i;
    int j;

    for (i = 0; i < t->cnt; i++) {
        const struct triangle *tr = &t->tr[i];
        int width = tr->line[tr->h - 1 - GARLAND_RISE] / 2;

        /* Hang a garland on a triangle. */
        for (j = -width; j < width + 1; j++) {
            int r = abs(j) == width ? GARLAND_RISE + 1 : GARLAND_RISE;

            attron(COLOR_PAIR(random(3, 7)));
            mvaddch(tr->y + tr->h - r, tr->x + j, GARLAND_SYM);
        }

        attron(COLOR_PAIR(2));
    }
}

void
tree_draw(const struct tree *t)
{
    int i;

    for (i = 0; i < t->cnt; i++)
        triangle_draw(&t->tr[i], t->k);

    trunk_draw(t->trunk, t->k);
}

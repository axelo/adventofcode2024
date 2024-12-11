#include "aoc.h"

#define N 131

typedef enum {
    UP     = 0,
    RIGHT  = 1,
    DOWN   = 2,
    LEFT   = 3
} Dir;

typedef struct {
    int x;
    int y;
    Dir d;
} Guard;

static int map[N][N];

static Guard find_start_pos(int size) {
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (map[y][x] == '^') return (Guard){.x = x, .y = y, .d = UP};
        }
    }

    assert(false);
}

static bool got_stuck(Guard g, int size, int ox, int oy) {
    if (g.x == ox && g.y == oy) return false;
    if (map[oy][ox] == '#') return false;

    bool hit_obstacle[N][N][4] = {0};

    for (;;) {
        int x = g.x + (g.d == LEFT ? -1 : g.d == RIGHT ? 1 : 0);
        int y = g.y + (g.d == UP   ? -1 : g.d == DOWN  ? 1 : 0);

        if (x < 0 || y < 0 || x >= size || y >= size) return false;

        if (map[y][x] == '#' || (x == ox && y == oy)) {
            if (hit_obstacle[g.y][g.x][g.d]) return true;

            hit_obstacle[g.y][g.x][g.d] = true;

            g.d = (g.d + 1) & 3;
        } else {
            g.x = x;
            g.y = y;
        }
    }
}

int main(void) {
    int size = aoc_read_square_map_from_stdin(N, map);

    Guard g = find_start_pos(size);

    int stuck = 0;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (got_stuck(g, size, x, y)) ++stuck;
        }
    }

    printf("%d\n", stuck);
    return 0;
}

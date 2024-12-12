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

int main(void) {
    int size = aoc_read_square_map_from_stdin(aoc_int_as_read, N, map);

    Guard g = find_start_pos(size);

    int visited = 0;

    for (;;) {
        if (!(map[g.y][g.x] & 0x80)) {
            ++visited;
            map[g.y][g.x] |= 0x80;
        }

        int x = g.x + (g.d == LEFT ? -1 : g.d == RIGHT ? 1 : 0);
        int y = g.y + (g.d == UP   ? -1 : g.d == DOWN  ? 1 : 0);

        if (x < 0 || y < 0 || x >= size || y >= size) break;

        if ((map[y][x] & 0x7f) == '#') {
            g.d = (g.d + 1) & 3;
        } else {
            g.x = x;
            g.y = y;
        }
    }

    printf("%d\n", visited);
    return 0;
}

#include "aoc.h"

#define G 71 // 7
#define N 3450

static aoc_Point_u8 coords[N];

static int mem[G][G] = {0};
static int visited[G][G] = {0};

static bool any_path(int b, uint8_t size, int8_t x, int8_t y) {
    if (x < 0 || y < 0 || x >= size || y >= size ||
        visited[y][x] == b) return false;

    visited[y][x] = b;

    if (mem[y][x] == '#') return false;

    if ((y == (size - 1)) && (x == (size - 1))) return true;

    return any_path(b, size, x - 1, y) ||
           any_path(b, size, x + 1, y) ||
           any_path(b, size, x, y + 1) ||
           any_path(b, size, x, y - 1);
}

int main(void) {
    int n_coords = 0;

    while (!feof(stdin)) {
        assert(n_coords < N);
        assert(aoc_read_from_stdin_base10_u8_truncate(&coords[n_coords].x));
        assert(aoc_read_from_stdin_char_and_chomp(','));
        assert(aoc_read_from_stdin_base10_u8_truncate(&coords[n_coords++].y));
        while (aoc_read_from_stdin_char_and_chomp('\n'));
    }

    uint8_t size = n_coords == 25 ? 7 : G;

    int b = 0;
    for (; b < n_coords; ++b) {
        mem[coords[b].y][coords[b].x] = '#';

        if (!any_path(b + 1, size, 0, 0)) break;
    }
    assert(b < n_coords);

    printf("%d,%d\n", coords[b].x, coords[b].y);
    return 0;
}

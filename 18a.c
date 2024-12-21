#include "aoc.h"

#define G 71
#define N 3450

static aoc_Point_u8 coords[N];

static int mem[G][G] = {0};
static int visited[G][G] = {0};

static int shortest_path(uint8_t size, int8_t x, int8_t y, int dist) {
    if (x < 0 || y < 0 || x >= size || y >= size) return - 1;

    if (visited[y][x] > 0 && visited[y][x] <= dist) return -1;

    visited[y][x] = dist;

    if (mem[y][x] == '#') return -1;

    if ((y == (size - 1)) && (x == (size - 1))) return dist;

    int dist_l = shortest_path(size, x - 1, y,     dist + 1);
    int dist_r = shortest_path(size, x + 1, y,     dist + 1);
    int dist_d = shortest_path(size, x,     y + 1, dist + 1);
    int dist_u = shortest_path(size, x,     y - 1, dist + 1);

    int min_dist = -1;

    if (dist_l > 0 && ((dist_l < min_dist) || (min_dist < 0))) min_dist = dist_l;
    if (dist_r > 0 && ((dist_r < min_dist) || (min_dist < 0))) min_dist = dist_r;
    if (dist_d > 0 && ((dist_d < min_dist) || (min_dist < 0))) min_dist = dist_d;
    if (dist_u > 0 && ((dist_u < min_dist) || (min_dist < 0))) min_dist = dist_u;

    return min_dist;
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

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x)
            mem[y][x] = '.';
    }

    int n_bytes = size == G ? 1024 : 12;

    for (int i = 0; i < n_bytes; ++i)
        mem[coords[i].y][coords[i].x] = '#';

    int dist = shortest_path(size, 0, 0, 0);

    printf("%d\n", dist);
    return 0;
}

#include "aoc.h"

#define N 54
#define N_SP 300

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

static int map[N][N];

static Point start_positions[N_SP];

int start_hiking(int d, bool end_found[N][N], int size, int x, int y) {
    int h = map[y][x];

    if (h >= 9) {
        if (!(end_found[y][x])) {
            end_found[y][x] = true;
            return 1;
        }

        return 0;
    }

    int xr = x + 1;
    int xl = x - 1;
    int yd = y + 1;
    int yu = y - 1;

    int n_found = 0;

    if (xr < size && (map[y][xr] - h) == 1)
        n_found += start_hiking(d + 1, end_found, size, xr, y);

    if (yd < size && (map[yd][x] - h) == 1)
        n_found += start_hiking(d + 1, end_found, size, x, yd);

    if (xl >= 0 && (map[y][xl] - h) == 1)
        n_found += start_hiking(d + 1, end_found, size, xl, y);

    if (yu >= 0 && (map[yu][x] - h) == 1)
        n_found += start_hiking(d + 1, end_found, size, x, yu);

    return n_found;
}

int main(void) {
    int size = aoc_read_square_map_from_stdin(aoc_digit_to_int, N, map);

    int n_start_positions = 0;

    for (uint8_t y = 0; y < size; ++y) {
        for (uint8_t x = 0; x < size; ++x) {
            if (map[y][x] == 0) {
                assert(n_start_positions < N_SP);
                start_positions[n_start_positions++] = (Point){.x = x, .y = y};
            }
        }
    }

    int sum = 0;

    for (int i = 0; i < n_start_positions; ++i) {
        bool end_found[N][N] = {0};

        sum += start_hiking(0, end_found, size, start_positions[i].x, start_positions[i].y);
    }

    printf("%d\n", sum);
    return 0;
}

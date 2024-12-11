#include "aoc.h"

#define N 51
#define P 630

static int map[N][N];

typedef struct {
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
} Pair;

static Pair pairs[P];

int main(void) {
    int size = aoc_read_square_map_from_stdin(N, map);

    int n_pairs = 0;

    for (uint8_t y0 = 0; y0 < size; ++y0) {
        for (uint8_t x0 = 0; x0 < size; ++x0) {
            if (map[y0][x0] != '.') {
                for (uint8_t y1 = 0; y1 < size; ++y1) {
                    for (uint8_t x1 = 0; x1 < size; ++x1) {
                        if (x0 != x1 && y0 != y1 && map[y0][x0] == map[y1][x1]) {
                            assert(n_pairs < P);
                            pairs[n_pairs++] = (Pair) {
                                .x0 = x0, .y0 = y0,
                                .x1 = x1, .y1 = y1
                            };
                        }
                    }
                }
            }
        }
    }

    int n_antinodes = 0;

    for (int i = 0; i < n_pairs; ++i) {
        int dx0 = pairs[i].x0 - pairs[i].x1;
        int dy0 = pairs[i].y0 - pairs[i].y1;
        int x0 = pairs[i].x0 + dx0;
        int y0 = pairs[i].y0 + dy0;

        if (x0 >= 0 && y0 >= 0 && x0 < size && y0 < size) {
            if (map[y0][x0] != '#') {
                map[y0][x0] = '#';
                ++n_antinodes;
            }
        }

        int dx1 = -dx0;
        int dy1 = -dy0;
        int x1 = pairs[i].x1 + dx1;
        int y1 = pairs[i].y1 + dy1;

        if (x1 >= 0 && y1 >= 0 && x1 < size && y1 < size) {
            if (map[y1][x1] != '#') {
                map[y1][x1] = '#';
                ++n_antinodes;
            }
        }
    }

    printf("%d\n", n_antinodes);
    return 0;
}

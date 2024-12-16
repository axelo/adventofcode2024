#include "aoc.h"

#define N 51
#define M 21
#define L 1001

static int map[N][N];
static int instructions[M][L];

int main(void) {
    int size = aoc_read_square_map_from_stdin(aoc_int_as_read, N, map);

    int n_instructions = 0;
    int n_moves = 0;

    while (!feof(stdin)) {
        assert(n_instructions < M);
        int read = aoc_read_from_stdin_line(aoc_int_as_read, L, instructions[n_instructions]);

        assert(read < L);

        if (!read) break;

        if (n_moves == 0) n_moves = read;

        assert(read = n_moves);

        ++n_instructions;
    }

    int rx = 0;
    int ry = 0;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (map[y][x] == '@') {
                rx = x;
                ry = y;
                goto r_pos_found;
            }
        }
    }
    r_pos_found:
    assert(rx != 0 && ry != 0);

    for (int i = 0; i < n_instructions; ++i) {
        for (int j = 0; j < n_moves; ++j) {
            switch(instructions[i][j]) {
            case '<':
                for (int x = rx - 1; x >= 0; --x) {
                    if (map[ry][x] == '#') break;

                    if (map[ry][x] == '.') {
                        for (int k = x; k < rx; ++k)
                            map[ry][k] = map[ry][k + 1];

                        map[ry][rx--] = '.';
                        break;
                    }
                }
                break;

            case '^':
                for (int y = ry - 1; y >= 0; --y) {
                    if (map[y][rx] == '#') break;

                    if (map[y][rx] == '.') {
                        for (int k = y; k < ry; ++k)
                            map[k][rx] = map[k + 1][rx];

                        map[ry--][rx] = '.';
                        break;
                    }
                }
                break;

            case '>':
                for (int x = rx + 1; x < size; ++x) {
                    if (map[ry][x] == '#') break;

                    if (map[ry][x] == '.') {
                        for (int k = x; k > rx; --k)
                            map[ry][k] = map[ry][k - 1];

                        map[ry][rx++] = '.';
                        break;
                    }
                }
                break;

            case 'v':
                for (int y = ry + 1; y < size; ++y) {
                    if (map[y][rx] == '#') break;

                    if (map[y][rx] == '.') {
                        for (int k = y; k > ry; --k)
                            map[k][rx] = map[k - 1][rx];

                        map[ry++][rx] = '.';
                        break;
                    }
                }
                break;

            default: assert(false);
            }
        }
    }

    int sum = 0;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (map[y][x] == 'O')
                sum += y * 100 + x;
        }
    }

    printf("%d\n", sum);
    return 0;
}

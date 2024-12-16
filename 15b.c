#include "aoc.h"

#define W (51 * 2)
#define H 51
#define M 21
#define L 1001
#define B 30

typedef struct {
    int x;
    int y;
} Box;

static int map[H][W];
static int instructions[M][L];

int main(void) {
    int org_map[H][H];
    int height = aoc_read_square_map_from_stdin(aoc_int_as_read, H, org_map);
    int width = height * 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < height; ++x) {
            switch (org_map[y][x]) {
            case '.':
                map[y][x * 2]     = '.';
                map[y][x * 2 + 1] = '.';
                break;
            case '#':
                map[y][x * 2]     = '#';
                map[y][x * 2 + 1] = '#';
                break;
            case 'O':
                map[y][x * 2]     = '[';
                map[y][x * 2 + 1] = ']';
                break;
            case '@':
                map[y][x * 2]     = '@';
                map[y][x * 2 + 1] = '.';
                break;
            default: assert(false);
            }
        }
    }

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

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == '@') {
                rx = x;
                ry = y;
                goto r_pos_found;
            }
        }
    }
    r_pos_found:
    assert(rx != 0 && ry != 0);

    Box boxes[100];

    for (int i = 0; i < n_instructions; ++i) {
        for (int j = 0; j < n_moves; ++j) {
            switch(instructions[i][j]) {
            case '^': {
                int y = ry - 1;

                if (map[y][rx] == '#') continue;
                else if (map[y][rx] == '.') {
                    map[ry--][rx] = '.';
                    map[ry][rx] = '@';
                }
                else {
                    int nboxes = 0;

                    if (map[y][rx] == '[')
                        boxes[nboxes++] = (Box) { .x = rx, .y = y };
                    else if (map[y][rx] == ']')
                        boxes[nboxes++] = (Box) { .x = rx - 1, .y = y };

                    bool can_move = true;

                    for (int k = 0; k < nboxes; ++k) {
                        int px = boxes[k].x;
                        int py = boxes[k].y - 1;

                        if (map[py][px] == '#' || map[py][px + 1] == '#') {
                            can_move = false;
                            break;
                        }

                        if (map[py][px] == '[') {
                            assert(nboxes < B);
                            boxes[nboxes++] = (Box) { .x = px, .y = py };
                        } else {
                            if (map[py][px] == ']') {
                                assert(nboxes < B);
                                boxes[nboxes++] = (Box) { .x = px - 1, .y = py };
                            }

                            if (map[py][px + 1] == '[') {
                                assert(nboxes < B);
                                boxes[nboxes++] = (Box) { .x = px + 1, .y = py };
                            }
                        }
                    }

                    if (can_move) {
                        for (int i = nboxes - 1; i >= 0; --i) {
                            map[boxes[i].y - 1][boxes[i].x] = '[';
                            map[boxes[i].y - 1][boxes[i].x + 1] = ']';
                            map[boxes[i].y][boxes[i].x] = '.';
                            map[boxes[i].y][boxes[i].x + 1] = '.';
                        }

                        map[ry--][rx] = '.';
                        map[ry][rx] = '@';
                    }
                }
            } break;

            case 'v': {
                int y = ry + 1;

                if (map[y][rx] == '#') continue;
                else if (map[y][rx] == '.') {
                    map[ry++][rx] = '.';
                    map[ry][rx] = '@';
                } else {
                    int nboxes = 0;

                    if (map[y][rx] == '[')
                        boxes[nboxes++] = (Box) { .x = rx, .y = y };
                    else if (map[y][rx] == ']')
                        boxes[nboxes++] = (Box) { .x = rx - 1, .y = y };

                    bool can_move = true;

                    for (int k = 0; k < nboxes; ++k) {
                        int px = boxes[k].x;
                        int py = boxes[k].y + 1;

                        if (map[py][px] == '#' || map[py][px + 1] == '#') {
                            can_move = false;
                            break;
                        }

                        if (map[py][px] == '[') {
                            assert(nboxes < B);
                            boxes[nboxes++] = (Box) { .x = px, .y = py };
                        } else {
                            if (map[py][px] == ']') {
                                assert(nboxes < B);
                                boxes[nboxes++] = (Box) { .x = px - 1, .y = py };
                            }

                            if (map[py][px + 1] == '[') {
                                assert(nboxes < B);
                                boxes[nboxes++] = (Box) { .x = px + 1, .y = py };
                            }
                        }
                    }

                    if (can_move) {
                        for (int i = nboxes - 1; i >= 0; --i) {
                            map[boxes[i].y + 1][boxes[i].x] = '[';
                            map[boxes[i].y + 1][boxes[i].x + 1] = ']';
                            map[boxes[i].y][boxes[i].x] = '.';
                            map[boxes[i].y][boxes[i].x + 1] = '.';
                        }

                        map[ry++][rx] = '.';
                        map[ry][rx] = '@';
                    }
                }
            } break;

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

            case '>':
                for (int x = rx + 1; x < width; ++x) {
                    if (map[ry][x] == '#') break;

                    if (map[ry][x] == '.') {
                        for (int k = x; k > rx; --k)
                            map[ry][k] = map[ry][k - 1];

                        map[ry][rx++] = '.';
                        break;
                    }
                }
                break;

            default: assert(false);
            }
        }
    }

    int sum = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == '[')
                sum += y * 100 + x;
        }
    }

    printf("%d\n", sum);
    return 0;
}

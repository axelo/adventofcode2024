#include "aoc.h"

#define N 200
#define M 6000

typedef struct {
    int x;
    int y;
} Coord;

static int letters[N][N];
static Coord coords[M];

static const char* mas = "MAS";

static bool match_next_letter(int* imas_ptr, int letter) {
    int i = *imas_ptr;
    assert(i < 4);

    char c = mas[i];

    if (c != letter) {
        if (letter == mas[0]) *imas_ptr = 1;
        else *imas_ptr = 0;
    } else {
        if (++i == 3) {
            *imas_ptr = 0;
            return true;
        }

        *imas_ptr = i;
    }

    return false;
}

static int search_diagonally(int s) {
    int n = 0;

    int dr = 0;
    int ul = 0;
    int dl = 0;
    int ur = 0;

    // Middle
    for (int y = 0; y < s; ++y) {
        // Down right
        if (match_next_letter(&dr, letters[y][y])) {
            assert(n < M);
            coords[n++] = (Coord){.x =  y - 1, .y =  y - 1};
        }

        // Up left
        if (match_next_letter(&ul, letters[s - y - 1][s - y - 1])) {
            assert(n < M);
            coords[n++] = (Coord){.x = s - y - 1 + 1, .y =  s - y - 1 + 1};
        }

        // Down left
        if (match_next_letter(&dl, letters[y][s - y - 1])) {
            assert(n < M);
            coords[n++] = (Coord){.x = s - y - 1 + 1, .y =  y - 1};
        }

        // Up right
        if (match_next_letter(&ur, letters[s - y - 1][y])) {
            assert(n < M);
            coords[n++] = (Coord){.x = y - 1, .y =  s - y - 1 + 1};
        }
    }

    // Above and below middle
    for (int sy = 1; sy < s; ++sy) {
        int dr_bm = 0;
        int ul_bm = 0;
        int dr_am = 0;
        int ul_am = 0;
        int dl_bm = 0;
        int ur_bm = 0;
        int dl_am = 0;
        int ur_am = 0;

        for (int y = sy; y < s; ++y) {
            // Down right below middle
            if (match_next_letter(&dr_bm, letters[y][y - sy])) {
                assert(n < M);
                coords[n++] = (Coord){.x = y - sy - 1, .y = y - 1};
            }

            // Down right above middle
            if (match_next_letter(&dr_am, letters[y - sy][y])) {
                assert(n < M);
                coords[n++] = (Coord){.x = y - 1, .y =  y - sy - 1};
            }

            // Up left below middle
            if (match_next_letter(&ul_bm, letters[sy - y - 1 + s][s - y - 1])) {
                assert(n < M);
                coords[n++] = (Coord){.x = s - y - 1 + 1, .y = sy - y - 1 + s + 1};
            }

            // Up left above middle
            if (match_next_letter(&ul_am, letters[s - y - 1][sy - y - 1 + s])) {
                assert(n < M);
                coords[n++] = (Coord){.x = sy - y - 1 + s + 1, .y = s - y - 1 + 1};
            }

            // Down left below middle
            if (match_next_letter(&dl_bm, letters[y][s - y + sy - 1])) {
                assert(n < M);
                coords[n++] = (Coord){.x = s - y + sy - 1 + 1, .y = y - 1};
            }

            // Up right below middle
            if (match_next_letter(&ur_bm, letters[s - y + sy - 1][y])) {
                assert(n < M);
                coords[n++] = (Coord){.x = y - 1, .y = s - y + sy - 1 + 1};
            }

            // Down left above middle
            if (match_next_letter(&dl_am, letters[y - sy][s - y - 1])) {
                assert(n < M);
                coords[n++] = (Coord){.x = s - y - 1 + 1, .y =  y - sy - 1};
            }

            // Up right above middle
            if (match_next_letter(&ur_am, letters[s - y - 1][y - sy])) {
                assert(n < M);
                coords[n++] = (Coord){.x = y - sy - 1, .y = s - y - 1 + 1};
            }
        }
    }

    return n;
}

int main (void) {
    int size = 0;
    int row = 0;

    assert((size = aoc_read_from_stdin_line(N, letters[row++])) <= N);
    assert(size > 0);

    while (!feof(stdin)) {
        int read = aoc_read_from_stdin_line(N, letters[row]);

        if (read) {
            assert(read == size);
            assert(++row < N);
        }
    }

    assert(row == size);

    int ncoords = search_diagonally(size);
    int xs = 0;

    for (int j = 0; j < ncoords; ++j) {
        for (int i = 0; i < ncoords; ++i) {
            if (i != j) {
                if (coords[j].x == coords[i].x && coords[j].y == coords[i].y) ++xs;
            }
        }
    }

    printf("%d\n", xs / 2);
    return 0;
}

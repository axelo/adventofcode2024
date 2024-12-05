#include "aoc.h"

#define N 200

static int letters[N][N];

static const char* xmas = "XMAS";

static bool match_next_letter(int* ixmas_ptr, int letter) {
    int i = *ixmas_ptr;
    assert(i < 5);

    char c = xmas[i];

    if (c != letter) {
        if (letter == xmas[0]) *ixmas_ptr = 1;
        else *ixmas_ptr = 0;
    } else {
        if (++i == 4) {
            *ixmas_ptr = 0;
            return true;
        }

        *ixmas_ptr = i;
    }

    return false;
}

static int search_straight(int s) {
    int n = 0;

    for (int x = 0; x < s; ++x) {
        int d = 0;
        int u = 0;
        int l = 0;
        int r = 0;

        for (int y = 0; y < s; ++y) {
            // Down
            if (match_next_letter(&d, letters[y][x])) ++n;

            // Up
            if (match_next_letter(&u, letters[s - y - 1][x])) ++n;

            // Right
            if (match_next_letter(&r, letters[x][y])) ++n;

            // Left
            if (match_next_letter(&l, letters[x][s - y - 1])) ++n;
        }
    }

    return n;
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
        if (match_next_letter(&dr, letters[y][y])) ++n;

        // // Up left
        if (match_next_letter(&ul, letters[s - y - 1][s - y - 1])) ++n;

        // // Down left
        if (match_next_letter(&dl, letters[y][s - y - 1])) ++n;

        // Up right
        if (match_next_letter(&ur, letters[s - y - 1][y])) ++n;
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
            if (match_next_letter(&dr_bm, letters[y][y - sy])) ++n;

            // Down right above middle
            if (match_next_letter(&dr_am, letters[y - sy][y])) ++n;

            // Up left below middle
            if (match_next_letter(&ul_bm, letters[sy - y - 1 + s][s - y - 1])) ++n;

            // Up left above middle
            if (match_next_letter(&ul_am, letters[s - y - 1][sy - y - 1 + s])) ++n;

            // Down left below middle
            if (match_next_letter(&dl_bm, letters[y][s - y + sy - 1])) ++n;

            // Up right below middle
            if (match_next_letter(&ur_bm, letters[s - y + sy - 1][y])) ++n;

            // Down left above middle
            if (match_next_letter(&dl_am, letters[y - sy][s - y - 1])) ++n;

            // Up right above middle
            if (match_next_letter(&ur_am, letters[s - y - 1][y - sy])) ++n;
        }
    }

    return n;
}

int main (void) {
    int s = 0;
    int row = 0;

    assert((s = aoc_read_from_stdin_line(N, letters[row++])) < N);
    assert(s > 0);

    while (!feof(stdin)) {
        int read = aoc_read_from_stdin_line(N, letters[row]);

        if (read) {
            assert(read == s);
            assert(++row < N);
        }
    }

    assert(row == s);

    int n = search_straight(s) + search_diagonally(s);

    printf("%d\n", n);
    return 0;
}

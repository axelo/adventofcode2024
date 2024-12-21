#include "aoc.h"

#define N 142

typedef enum {
    RIGHT = 0,
    DOWN,
    LEFT,
    UP
} Dir;

static int map[N][N];

static int visited[N][N][4] = {0};

static int move(int rx, int ry, Dir rdir, int score) {
    if (visited[ry][rx][rdir] == 0) {
        visited[ry][rx][rdir] = score;
    } else {
        if (visited[ry][rx][rdir] <= score) return -1;

        visited[ry][rx][rdir] = score;
    }

    if (map[ry][rx] == '#') return -1;
    if (map[ry][rx] == 'E') return score;

    switch (rdir) {
    case RIGHT: {
        int rscore = move(rx + 1, ry, RIGHT, score + 1);
        int dscore = move(rx, ry, DOWN, score + 1000);
        int uscore = move(rx, ry, UP, score + 1000);

        int min_score = -1;

        if (rscore > 0 && ((rscore < min_score) || (min_score < 0))) min_score = rscore;
        if (dscore > 0 && ((dscore < min_score) || (min_score < 0))) min_score = dscore;
        if (uscore > 0 && ((uscore < min_score) || (min_score < 0))) min_score = uscore;

        return min_score;
    };

    case DOWN: {
        int dscore = move(rx, ry + 1, DOWN, score + 1);
        int lscore = move(rx, ry, LEFT, score + 1000);
        int rscore = move(rx, ry, RIGHT, score + 1000);

        int min_score = -1;

        if (dscore > 0 && (dscore < min_score || min_score < 0)) min_score = dscore;
        if (lscore > 0 && (lscore < min_score || min_score < 0)) min_score = lscore;
        if (rscore > 0 && (rscore < min_score || min_score < 0)) min_score = rscore;

        return min_score;
    };

    case LEFT: {
        int lscore = move(rx - 1, ry, LEFT, score + 1);
        int dscore = move(rx, ry, DOWN, score + 1000);
        int uscore = move(rx, ry, UP, score + 1000);

        int min_score = -1;

        if (lscore > 0 && (lscore < min_score || min_score < 0)) min_score = lscore;
        if (dscore > 0 && (dscore < min_score || min_score < 0)) min_score = dscore;
        if (uscore > 0 && (uscore < min_score || min_score < 0)) min_score = uscore;

        return min_score;
    };

    case UP: {
        int uscore = move(rx, ry - 1, UP, score + 1);
        int lscore = move(rx, ry, LEFT, score + 1000);
        int rscore = move(rx, ry, RIGHT, score + 1000);

        int min_score = -1;

        if (uscore > 0 && (uscore < min_score || min_score < 0)) min_score = uscore;
        if (lscore > 0 && (lscore < min_score || min_score < 0)) min_score = lscore;
        if (rscore > 0 && (rscore < min_score || min_score < 0)) min_score = rscore;

        return min_score;
    };
    }

    return score;
}

int main(void) {
    int size = aoc_read_square_map_from_stdin(aoc_int_as_read, N, map);

    int sx = 0;
    int sy = 0;

    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            if (map[y][x] == 'S') {
                sx = x;
                sy = y;
                goto start_found;
            }

    start_found:
    assert(sx != 0 && sy != 0);

    int score = move(sx, sy, RIGHT, 0);

    printf("%d\n", score);
    return 0;
}

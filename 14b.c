#include "aoc.h"

#define N 500

#define W 101
#define H 103
#define HALF_W (W/2)
#define HALF_H (H/2)

typedef struct {
    int64_t x;
    int64_t y;
    int64_t vx;
    int64_t vy;
} Robot;

static Robot robots[N];
static int map[H][W] = {0};

static inline int64_t modulo(int64_t a, int64_t b) {
    int64_t rem = a % b;

    return rem < 0
        ? b < 0
            ? rem - b
            : rem + b
        : rem;
}

static void print_robots(int n_robots, int t) {
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (map[y][x] == t) putchar('#');
            else putchar('.');
        }
        putchar('\n');
    }
}

int main(void) {
    int n_robots = 0;

    while (!feof(stdin)) {
        assert(n_robots < N);
        assert(aoc_read_from_stdin_string_and_chomp("p="));
        assert(aoc_read_from_stdin_base10_s64(&robots[n_robots].x));
        assert(aoc_read_from_stdin_char_and_chomp(','));
        assert(aoc_read_from_stdin_base10_s64(&robots[n_robots].y));
        assert(aoc_read_from_stdin_string_and_chomp(" v="));
        assert(aoc_read_from_stdin_base10_s64(&robots[n_robots].vx));
        assert(aoc_read_from_stdin_char_and_chomp(','));
        assert(aoc_read_from_stdin_base10_s64(&robots[n_robots].vy));
        while (aoc_read_from_stdin_char_and_chomp('\n'));

        ++n_robots;
    }

    int t = 1; // assume 0 isn't a tree

    for (;; ++t) {
        int i = 0;

        for (; i < n_robots; ++i) {
            int64_t x = modulo(robots[i].x + (robots[i].vx * t), W);
            int64_t y = modulo(robots[i].y + (robots[i].vy * t), H);

            if (map[y][x] == t) break;

            map[y][x] = t;
        }

        if (i == n_robots) {
            print_robots(n_robots, t);
            break;
        }
    }

    printf("%d\n", t);
    return 0;
}

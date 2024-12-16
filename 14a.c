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

static inline int64_t modulo(int64_t a, int64_t b) {
    int64_t rem = a % b;

    return rem < 0
        ? b < 0
            ? rem - b
            : rem + b
        : rem;
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

    int n_q1 = 0;
    int n_q2 = 0;
    int n_q3 = 0;
    int n_q4 = 0;

    for (int i = 0; i < n_robots; ++i) {
        int64_t x = modulo(robots[i].x + robots[i].vx * 100, W);
        int64_t y = modulo(robots[i].y + robots[i].vy * 100, H);

        if      (x < HALF_W && y < HALF_H) ++n_q1;
        else if (x > HALF_W && y < HALF_H) ++n_q2;
        else if (x < HALF_W && y > HALF_H) ++n_q3;
        else if (x > HALF_W && y > HALF_H) ++n_q4;
    }

    int64_t factor =
        (n_q1 == 0 ? 1 : n_q1) *
        (n_q2 == 0 ? 1 : n_q2) *
        (n_q3 == 0 ? 1 : n_q3) *
        (n_q4 == 0 ? 1 : n_q4);

    printf("%lld\n", factor);
    return 0;
}

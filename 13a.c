#include "aoc.h"

#define N 1000

typedef struct {
    int64_t ax;
    int64_t ay;

    int64_t bx;
    int64_t by;

    int64_t px;
    int64_t py;
} Machine;

static Machine machines[N];

int main(void) {
    int n_machines = 0;

    while(!feof(stdin)) {
        assert(n_machines < N);
        assert(aoc_read_from_stdin_string_and_chomp("Button A: X+"));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].ax));
        assert(aoc_read_from_stdin_string_and_chomp(", Y+"));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].ay));
        assert(aoc_read_from_stdin_char_and_chomp('\n'));
        assert(aoc_read_from_stdin_string_and_chomp("Button B: X+"));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].bx));
        assert(aoc_read_from_stdin_string_and_chomp(", Y+"));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].by));
        assert(aoc_read_from_stdin_char_and_chomp('\n'));
        assert(aoc_read_from_stdin_string_and_chomp("Prize: X="));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].px));
        assert(aoc_read_from_stdin_string_and_chomp(", Y="));
        assert(aoc_read_from_stdin_base10_s64(&machines[n_machines].py));
        while (aoc_read_from_stdin_char_and_chomp('\n'));

        ++n_machines;
    }

    int64_t tokens = 0;

    for (int i = 0; i < n_machines; ++i) {
        for (int a = 0; a < 100; ++a) {
            for (int b = 0; b < 100; ++b) {
                int64_t px = a * machines[i].ax + b * machines[i].bx;
                int64_t py = a * machines[i].ay + b * machines[i].by;

                if (px == machines[i].px && py == machines[i].py) {
                    tokens += a * 3 + b;
                    break;
                }

            }
        }
    }

    printf("%lld\n", tokens);
    return 0;
}

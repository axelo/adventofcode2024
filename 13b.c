#include "aoc.h"

#define N 400

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

        machines[n_machines].px += 10000000000000;
        machines[n_machines].py += 10000000000000;

        ++n_machines;
    }

/*
Uinsg https://www.youtube.com/watch?v=95zVTo2nu3Q

Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

94a + 22b = 8400
34a + 67b = 5400

| 94 22 | = (94*67) - (22*34) = 5550 = D
| 34 67 |

| 8400 22 | = (8400*67) - (22*5400) = 444000 = Da
| 5400 67 |

| 94 8400 | = (94*5400) - (8400*34) = 222000 = Db
| 34 5400 |

a = Da / D = 80
b = Db / D = 40
*/
    int64_t tokens = 0;

    for (int i = 0; i < n_machines; ++i) {
        int64_t D = (machines[i].ax *  machines[i].by) - (machines[i].bx *  machines[i].ay);
        assert(D != 0);

        int64_t Da = (machines[i].px * machines[i].by) - (machines[i].bx * machines[i].py);
        int64_t Db = (machines[i].ax * machines[i].py) - (machines[i].px * machines[i].ay);

        int64_t a = Da / D;
        int64_t b = Db / D;

        if (a * machines[i].ax + b * machines[i].bx == machines[i].px &&
            a * machines[i].ay + b * machines[i].by == machines[i].py) {

            tokens += 3 * a + b;
        }
    }

    printf("%lld\n", tokens);
    return 0;
}

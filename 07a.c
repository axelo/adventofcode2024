#include "aoc.h"

#define N 1000
#define M 12

static int64_t results[N];
static int nvalues[N];
static int64_t values[N][M];

int main(void) {
    int parse_state = 0;

    int nresult = 0;
    int nvalue = 0;

    while (!feof(stdin)) {
        if (parse_state == 0) {
            assert(nresult < N);
            assert(aoc_read_from_stdin_base10_s64(&results[nresult]));
            assert(aoc_read_from_stdin_char_and_chomp(':'));
            assert(aoc_read_from_stdin_char_and_chomp(' '));
            parse_state = 1;
        } else if (parse_state == 1) {
            assert(nvalue < M);
            assert(aoc_read_from_stdin_base10_s64(&values[nresult][nvalue++]));

            if (!aoc_read_from_stdin_char_and_chomp(' ')) {
                nvalues[nresult++] = nvalue;
                nvalue = 0;

                aoc_read_from_stdin_until_digit();
                parse_state = 0;
            }
        }
    }

    int64_t sum = 0;

    for (int i = 0; i < nresult; ++i) {
        int perms = 1 << (nvalues[i] - 1);

        for (int p = 0; p < perms; ++p) {
            int64_t res = values[i][0];

            for (int j = 1; j < nvalues[i]; ++j) {
                int op = (p & (1 << (j - 1))) ? 1 : 0;

                int64_t value = values[i][j];

                res = op == 0 ? res + value : res * value;
            }

            if (res == results[i]) {
                sum += res;
                break;
            }
        }
    }

    printf("%lld\n", sum);
    return 0;
}

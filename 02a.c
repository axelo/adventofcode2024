#include "aoc.h"

#define NLEVELS  8000
#define NREPORTS 1000

typedef struct {
    int i;
    int n;
} Report;

static int64_t levels[NLEVELS];
static Report reports[NREPORTS];

static bool safe_report(Report report) {
    assert(report.n >= 2);

    int64_t dir_bit = aoc_sign_bit_s64(levels[report.i + 1] - levels[report.i]);

    for (int i = report.i; i < report.n - 1; ++i) {
        int64_t diff = levels[i + 1] - levels[i];

        if (dir_bit != aoc_sign_bit_s64(diff)) return false;

        int64_t abs_diff = llabs(diff);

        if (abs_diff < 1 || abs_diff > 3) return false;
    }

    return true;
}

int main(void) {
    int nreports = 0;
    int nlevels = 0;
    int i = 0;

    int64_t* level_ptr = levels;

    while (!feof(stdin)) {
        assert(nlevels++ < NLEVELS);

        assert(aoc_read_from_stdin_base10_s64(level_ptr++) == RES_READ_NUMBER_OK);

        if (aoc_read_from_stdin_until_digit_stop_on_newlines()) {
            assert(nreports < NREPORTS);

            reports[nreports++] = (Report){.i = i, .n = nlevels};

            i = nlevels;
        }
    }

    int nsafe = 0;

    for (int i = 0; i < nreports; ++i)
        if (safe_report(reports[i])) ++nsafe;

    printf("%d\n", nsafe);
    return 0;
}

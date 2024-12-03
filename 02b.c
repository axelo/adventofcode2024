#include "aoc.h"

#define NLEVELS  8000
#define NREPORTS 1000

typedef struct {
    int i;
    int n;
} Report;

static int64_t levels[NLEVELS];
static Report reports[NREPORTS];

static bool safe_report_with_dampener(Report report, int damp_i) {
    int64_t prev_diff = 0;

    for (int i = report.i; i < report.n - 1; ++i) {
        if (i == damp_i) continue;

        int next_i = i + 1;

        if (next_i == damp_i)
            if (++next_i == report.n) break;

        int64_t diff = levels[next_i] - levels[i];

        int64_t abs_diff = llabs(diff);

        if (abs_diff < 1 || abs_diff > 3) return false;

        if (prev_diff != 0 && aoc_sign_bit_s64(diff) != aoc_sign_bit_s64(prev_diff)) return false;

        prev_diff = diff;
    }

    return true;
}

static bool safe_report(Report report) {
    for (int damp_i = report.i - 1; damp_i < report.n; ++damp_i)
        if (safe_report_with_dampener(report, damp_i)) return true;

    return false;
}

int main(void) {
    int nreports = 0;
    int nlevels = 0;
    int i = 0;

    int64_t* level_ptr = levels;

    while (!feof(stdin)) {
        assert(nlevels++ < NLEVELS);

        assert(aoc_read_from_stdin_base10_s64(level_ptr++));

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

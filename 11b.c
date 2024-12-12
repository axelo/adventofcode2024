#include "aoc.h"

#define BLINKS 75
#define I 10
#define K 4000

static int64_t count[2][K];
static int64_t keys[2][K];
static int     n_keys[2];

static void count_stone(int j, int64_t s, int64_t c) {
    int n = n_keys[j];

    for (int k = 0; k < n; ++k) {
        if (keys[j][k] == s) {
            count[j][k] += c;
            return;
        }
    }

    assert(n < K);
    keys[j][n] = s;
    count[j][n] = c;

    ++n_keys[j];
}

static int divider(int64_t i) {
    if (i < 10)            return -1;
    if (i < 100)           return 10;
    if (i < 1000)          return -1;
    if (i < 10000)         return 100;
    if (i < 100000)        return -1;
    if (i < 1000000)       return 1000;
    if (i < 10000000)      return -1;
    if (i < 100000000)     return 10000;
    if (i < 1000000000)    return -1;
    if (i < 10000000000)   return 100000;
    if (i < 100000000000)  return -1;
    if (i < 1000000000000) return 1000000;
    assert(false);
}

int main(void) {
    int64_t input[I];
    int n_input = 0;

    while(!feof(stdin)) {
        assert(n_input < I);
        aoc_read_from_stdin_base10_s64(&input[n_input++]);
        aoc_read_from_stdin_until_digit();
    }

    int64_t n = 0;

    for (int i = 0; i < n_input; ++i) {
        keys[0][0] = input[i];
        count[0][0] = 1;
        n_keys[0] = 1;
        n_keys[1] = 0;

        int ki;
        int kj;

        for (int b = 0; b < BLINKS; ++b) {
            ki = b & 1;
            kj = ki == 0 ? 1 : 0;
            n_keys[kj] = 0;

            for (int j = 0; j < n_keys[ki]; ++j) {
                int64_t stone = keys[ki][j];
                int64_t c = count[ki][j];
                assert(c > 0);

                if (stone == 0) count_stone(kj, 1, c);
                else {
                    int div = divider(stone);

                    if (div < 0) count_stone(kj, stone * 2024, c);
                    else {
                        int64_t left  = stone / div;
                        int64_t right = stone % div;

                        count_stone(kj, left, c);
                        count_stone(kj, right, c);
                    }
                }
            }
        }

        for (int i = 0; i < n_keys[kj]; ++i)
           n += count[kj][i];
    }

    printf("%lld\n", n);
    return 0;
}

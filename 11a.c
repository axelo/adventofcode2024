#include "aoc.h"

#define BLINKS 25
#define N (BLINKS + 1)
#define M 200000

static int64_t stones[N][M];
static int n_stones[N];

static int divider(int64_t i) {
    if (i < 10) return -1;
    if (i < 100) return 10;
    if (i < 1000) return -1;
    if (i < 10000) return 100;
    if (i < 100000) return -1;
    if (i < 1000000) return 1000;
    if (i < 10000000) return -1;
    if (i < 100000000) return 10000;
    if (i < 1000000000) return -1;
    if (i < 10000000000) return 100000;
    if (i < 100000000000) return -1;
    if (i < 1000000000000) return 1000000;
    assert(false);
}

int main(void) {
    int64_t stone;
    n_stones[0] = 0;

    while(!feof(stdin)) {
        if (aoc_read_from_stdin_base10_s64(&stone)) {
            int i = n_stones[0]++;
            assert(i < M);

            stones[0][i++] = (int)stone;
        }

        aoc_read_from_stdin_until_digit();
    }

    for (int next_b_i = 1; next_b_i < N; ++next_b_i) {
        n_stones[next_b_i] = 0;

        for (int i = 0; i < n_stones[next_b_i - 1]; ++i) {
            int64_t s = stones[next_b_i - 1][i];

            int j = n_stones[next_b_i];
            assert(j < M);

            if (s == 0) stones[next_b_i][j++] = 1;
            else {
                int div = divider(s);

                if (div < 0) stones[next_b_i][j++] = s * 2024;
                else {
                    int64_t left  = s / div;
                    int64_t right = s % div;

                    stones[next_b_i][j++] = left;

                    assert(j < M);
                    stones[next_b_i][j++] = right;
                }
            }

            n_stones[next_b_i] = j;
        }
    }

    printf("%d\n", n_stones[BLINKS]);
    return 0;
}

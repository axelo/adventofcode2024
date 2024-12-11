#include "aoc.h"

#define N 100000

typedef enum {
    READ_BLOCKS,
    READ_FREE_SPACE,
} STATE;

static int disk[N];

int main(void) {
    STATE state = READ_BLOCKS;
    int id = 0;
    int n = 0;

    for (int c = getchar(); c != '\n' && c != EOF; c = getchar()) {
        switch (state) {
        case READ_BLOCKS:
            for (int i = 0; i < c - '0'; ++i) {
                assert(n < N);
                disk[n++] = id;
            }

            ++id;
            state = READ_FREE_SPACE;
            break;

        case READ_FREE_SPACE:
            for (int i = 0; i < c - '0'; ++i) {
                assert(n < N);
                disk[n++] = -1;
            }

            state = READ_BLOCKS;
            break;
        }
    }

    int k = 0;

    for (int i = n - 1; i >= 0; --i) {
        if (i < k) break;

        if (disk[i] < 0) continue;

        for (int j = k; j < i; ++j) {
            if (disk[j] >= 0) continue;

            disk[j] = disk[i];
            disk[i] = -1;
            k = j + 1;

            break;
        }
    }

    int64_t checksum = 0;

    for (int i = 0; i < n; ++i) {
        if (disk[i] >= 0) checksum += i * disk[i];
        else break;
    }

    printf("%lld\n", checksum);
    return 0;
}

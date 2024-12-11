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

    for (int i = n - 1; i >= 0; --i) {
        int id = disk[i];

        if (id < 0) continue;

        int j = i;
        for (; j >= 0 && disk[j] == id; --j);
        int blocks = i - j;

        for (j = 0; j < i; ++j) {
            if (disk[j] >= 0) continue;

            int k = 0;
            for (; k < blocks; ++k) {
                if (disk[j + k] >= 0) break;
            }

            if (k != blocks) continue;

            for (k = 0; k < blocks; ++k) {
                disk[j + k] = id;
                disk[i - k] = -1;
            }

            break;
        }

        i -= blocks - 1;
    }

    int64_t checksum = 0;

    for (int i = 0; i < n; ++i)
        if (disk[i] >= 0) checksum += i * disk[i];

    printf("%lld\n", checksum);
    return 0;
}

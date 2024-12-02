#include <assert.h> // assert
#include <limits.h> // INT_MAX
#include <stdbool.h>
#include <stdint.h> // int_t
#include <stdio.h>  // flockfile, funlockfile, getchar_unlocked, ungetcs
#include <stdlib.h> // qsort, llabs

typedef enum {
    RES_READ_NUMBER_OK            = 0,
    RES_READ_NUMBER_ERR_NO_DIGITS = 1,
    RES_READ_NUMBER_ERR_OVERFLOW  = 2,
} RES_READ_NUMBER;

#define MAX_INT_BASE10_ONE_BEFORE (INT_MAX / 10)

static RES_READ_NUMBER aoc_read_from_stdin_base10_s64(int64_t* ptr_to_s64) {
    int64_t buffer[32];
    int len = 0;
    int c;

    flockfile(stdin);

    for (;;) {
        c = getchar_unlocked();

        if (c < '0' || c > '9') break;

        buffer[len++] = (int64_t)(c - '0');
    }

    funlockfile(stdin);

    if (c != EOF) ungetc(c, stdin);

    if (len == 0) return RES_READ_NUMBER_ERR_NO_DIGITS;

    int64_t num = 0;

    for (int i = 0; i < len; ++i) {
        if (num > MAX_INT_BASE10_ONE_BEFORE) return RES_READ_NUMBER_ERR_OVERFLOW;

        num *= 10;
        num += buffer[i];
    }

    *ptr_to_s64 = num;

    return RES_READ_NUMBER_OK;
}

static void aoc_read_from_stdin_until_digit(void) {
    int c;

    flockfile(stdin);

    do {
        c = getchar_unlocked();
    } while (c != EOF && (c < '0' || c > '9'));

    funlockfile(stdin);

    if (c != EOF) ungetc(c, stdin);
}

// will chomp all new lines found
static bool aoc_read_from_stdin_until_digit_stop_on_newlines(void) {
    bool unget = true;
    bool newlines_found = false;
    int c;

    flockfile(stdin);

    do {
        c = getchar_unlocked();

        if (c == EOF || c == '\n') {
            while (c == '\n') c = getchar_unlocked();

            unget = c != EOF;
            newlines_found = true;
            break;
        }
    } while (c < '0' || c > '9');

    funlockfile(stdin);

    if (unget) ungetc(c, stdin);

    return newlines_found;
}

static int aoc_compare_s64_ptr(const int64_t* a, const int64_t* b) {
    if (*a < *b)      return -1;
    else if (*a > *b) return 1;
    else              return 0;
}

static void aoc_sort_in_place_s64(int n, int64_t xs[n]) {
    qsort(xs, (size_t)n, sizeof(int64_t), (int (*)(const void *, const void *)) aoc_compare_s64_ptr);
}

static inline int aoc_sign_bit_s64(int64_t x) {
    return (uint64_t)x >> 63;
}

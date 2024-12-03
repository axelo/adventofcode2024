#include <assert.h> // assert
#include <limits.h> // INT_MAX
#include <stdbool.h>
#include <stdint.h> // int_t
#include <stdio.h>  // flockfile, funlockfile, getchar_unlocked, ungetcs
#include <stdlib.h> // qsort, llabs

#define MAX_INT_BASE10_ONE_BEFORE (INT_MAX / 10)

static bool aoc_read_from_stdin_base10_s64(int64_t* ptr_to_s64) {
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

    if (len == 0) return false;

    int64_t num = 0;

    for (int i = 0; i < len; ++i) {
        assert(num <= MAX_INT_BASE10_ONE_BEFORE);

        num *= 10;
        num += buffer[i];
    }

    *ptr_to_s64 = num;

    return true;
}

static bool aoc_read_from_stdin_char_and_chomp(char expected_char) {
    int c = getchar();
    bool found = c == expected_char;

    if (!found && c != EOF) ungetc(c, stdin);

    return found;
}

static bool aoc_read_from_stdin_until_string_and_chomp(const char* string) {
    const char* source_ptr = string;
    int source_c = -1;

    flockfile(stdin);

    for (;;) {
        source_c = *source_ptr++;

        if (source_c == 0) break;

        int c = getchar_unlocked();

        if (c == EOF) break;

        if (c != source_c) source_ptr = string;
    }

    funlockfile(stdin);

    return source_c == 0;
}

// returns 0 if no strings found, otherwise 1 for first, 2 for second, 3 for third.
static int aoc_read_from_stdin_until_one_of_string_and_chomp(const char* s1, const char* s2, const char* s3) {
    const char* s1_ptr = s1;
    const char* s2_ptr = s2;
    const char* s3_ptr = s3;

    int i = 0;

    flockfile(stdin);

    for (;;) {
        int c1 = *s1_ptr++;
        int c2 = *s2_ptr++;
        int c3 = *s3_ptr++;

        if (c1 == 0) {
            i = 1;
            break;
        } else if (c2 == 0) {
            i = 2;
            break;
        } else if (c3 == 0) {
            i = 3;
            break;
        }

        int c = getchar_unlocked();

        if (c == EOF) break;

        if (c != c1) s1_ptr = s1;
        if (c != c2) s2_ptr = s2;
        if (c != c3) s3_ptr = s3;
    }

    funlockfile(stdin);

    return i;
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

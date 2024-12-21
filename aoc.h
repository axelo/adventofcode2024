#include <assert.h> // assert
#include <limits.h> // INT_MAX
#include <stdbool.h>
#include <stdint.h> // int_t
#include <stdio.h>  // flockfile, funlockfile, getchar_unlocked, ungetcs
#include <stdlib.h> // qsort, llabs

#define MAX_INT64_BASE10_ONE_BEFORE (INT64_MAX / 10)

typedef struct {
    uint8_t x;
    uint8_t y;
} aoc_Point_u8;

static bool aoc_read_from_stdin_base10_s64(int64_t* ptr_to_s64) {
    int64_t buffer[32];
    int len = 0;
    int c;
    bool negative = false;

    flockfile(stdin);

    c = getchar_unlocked();

    if (c == '-') {
        negative = true;
        c = getchar_unlocked();
    }

    for (;;) {
        if (c < '0' || c > '9') break;

        buffer[len++] = (int64_t)(c - '0');

        c = getchar_unlocked();
    }

    funlockfile(stdin);

    if (c != EOF) ungetc(c, stdin);

    if (len == 0) return false;

    int64_t num = 0;

    for (int i = 0; i < len; ++i) {
        assert(num <= MAX_INT64_BASE10_ONE_BEFORE);

        num *= 10;
        num += buffer[i];
    }

    *ptr_to_s64 = negative ? -num : num;

    return true;
}

static bool aoc_read_from_stdin_base10_s32_truncate(int32_t* ptr_to_s32) {
    int64_t i;
    if (aoc_read_from_stdin_base10_s64(&i)) {
        *ptr_to_s32 = (int32_t)i;
        return true;
    }
    return false;
}

static bool aoc_read_from_stdin_base10_u8_truncate(uint8_t* ptr_to_u8) {
    int64_t i;
    if (aoc_read_from_stdin_base10_s64(&i)) {
        *ptr_to_u8 = (uint8_t)i;
        return true;
    }
    return false;
}

static bool aoc_read_from_stdin_char_and_chomp(char expected_char) {
    int c = getchar();
    bool found = c == expected_char;

    if (!found && c != EOF) ungetc(c, stdin);

    return found;
}

static bool aoc_read_from_stdin_string_and_chomp(const char* expected_string) {
    const char* source_ptr = expected_string;
    int source_c = -1;

    flockfile(stdin);

    for (;;) {
        source_c = *source_ptr++;

        if (source_c == 0) break;

        int c = getchar_unlocked();

        if (c!= source_c || c == EOF) break;
    }

    funlockfile(stdin);

    return source_c == 0;
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

static bool aoc_read_from_stdin_until_digit(void) {
    int c;

    flockfile(stdin);

    do {
        c = getchar_unlocked();
    } while (c != EOF && (c < '0' || c > '9'));

    funlockfile(stdin);

    if (c != EOF) ungetc(c, stdin);

    return c != EOF;
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

static int aoc_read_from_stdin_line(int (*map_fn)(int), int n, int source[n]) {
    int i = 0;

    flockfile(stdin);

    for (;;) {
        int c = getchar_unlocked();

        if (c == '\n' || c == EOF) break;

        if (i >= n) {
            ++i;
            break;
        }

        source[i++] = map_fn(c);
    }

    funlockfile(stdin);

    return i;
}

static int aoc_int_as_read(int i) {
    return i;
}

static int aoc_digit_to_int(int i) {
    return i - '0';
}

static int aoc_read_square_map_from_stdin(int (*map_fn)(int), int n, int map[n][n]) {
    int row = 0;
    int size = aoc_read_from_stdin_line(map_fn, n, map[row++]);
    assert(size > 0 && size <= n);

    while (!feof(stdin)) {
        assert(row < n);
        int read = aoc_read_from_stdin_line(map_fn, n, map[row]);

        if (!read) break;

        assert(read == size);

        ++row;
    }

    assert(row == size);
    return size;
}

static int aoc_compare_s64_ptr(const int64_t* a, const int64_t* b) {
    if (*a < *b)      return -1;
    else if (*a > *b) return 1;
    else              return 0;
}

static void aoc_sort_in_place_s64(int n, int64_t xs[n]) {
    qsort(xs, (size_t)n, sizeof(int64_t), (int (*)(const void *, const void *)) aoc_compare_s64_ptr);
}

static void aoc_sort_in_place_s32(int n, int32_t xs[n], int (*compare)(const int32_t *, const int32_t *)) {
    qsort(xs, (size_t)n, sizeof(int32_t), (int (*)(const void *, const void *)) compare);
}

static inline int aoc_sign_bit_s64(int64_t x) {
    return (uint64_t)x >> 63;
}

static void aoc_print_map(int n, int map[n][n], int size) {
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            putchar(map[y][x]);
        }
        putchar('\n');
    }
}

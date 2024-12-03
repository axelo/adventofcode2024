#include "aoc.h"

int main (void) {
    int64_t a;
    int64_t b;

    int64_t sum = 0;

    while (!feof(stdin)) {
        if (!aoc_read_from_stdin_until_string_and_chomp("mul(")) continue;
        if (!aoc_read_from_stdin_base10_s64(&a)) continue;
        if (!aoc_read_from_stdin_char_and_chomp(',')) continue;
        if (!aoc_read_from_stdin_base10_s64(&b)) continue;
        if (!aoc_read_from_stdin_char_and_chomp(')')) continue;

        sum += a * b;
    }

    printf("%lld\n", sum);
    return 0;
}

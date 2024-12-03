#include "aoc.h"

int main (void) {
    int64_t a;
    int64_t b;
    int i;

    bool do_multiply = true;
    int64_t sum = 0;

    while (!feof(stdin)) {
        if (!(i = aoc_read_from_stdin_until_one_of_string_and_chomp("mul(", "do()", "don't()"))) continue;

        if (i == 1) {
            if (!aoc_read_from_stdin_base10_s64(&a)) continue;
            if (!aoc_read_from_stdin_char_and_chomp(',')) continue;
            if (!aoc_read_from_stdin_base10_s64(&b)) continue;
            if (!aoc_read_from_stdin_char_and_chomp(')')) continue;

            if (do_multiply) sum += a * b;
        } else
            do_multiply = i == 2;
    }

    printf("%lld\n", sum);
    return 0;
}

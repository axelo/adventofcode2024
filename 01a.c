#include "aoc.h"

#define N 1000

static int64_t location_ids_a[N];
static int64_t location_ids_b[N];

int main(void) {
    int64_t* ptr_location_id_a = location_ids_a;
    int64_t* ptr_location_id_b = location_ids_b;
    int n = 0;

    while (!feof(stdin)) {
        assert(aoc_read_from_stdin_base10_s64(ptr_location_id_a++));
        aoc_read_from_stdin_until_digit();

        assert(aoc_read_from_stdin_base10_s64(ptr_location_id_b++));
        aoc_read_from_stdin_until_digit();

        assert(n++ < N);
    }

    aoc_sort_in_place_s64(n, location_ids_a);
    aoc_sort_in_place_s64(n, location_ids_b);

    int64_t sum = 0;

    for (int i = 0; i < n; ++i) sum += llabs(location_ids_a[i] - location_ids_b[i]);

    printf("%lld\n", sum);
    return 0;
}

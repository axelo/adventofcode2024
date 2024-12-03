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

    int64_t sum = 0;

    for (int i = 0; i < n; ++i) {
        int nfound = 0;

        for (int j = 0; j < n; ++j)
            if (location_ids_a[i] == location_ids_b[j]) ++nfound;

        sum += nfound * location_ids_a[i];
    }

    printf("%lld\n", sum);
    return 0;
}

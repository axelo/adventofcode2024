#include "aoc.h"

#define N 1000
#define M 12
#define P 531441 // 3^12
#define Q 30

static int64_t results[N];

static int nvalues[N];
static int64_t values[N][M];

static int permutations[M][P][M];
static int npermutations[M];
static int queues[Q][M];

static int generate_permutations(int n_ops, int n_values, int permutations[P][M]) {
    int nperms = 0;
    int queues_n[Q];
    int qi = 0;

    for (int i = 0; i < n_ops; ++i) {
        queues[qi][0] = i;
        queues_n[qi] = 1;
        ++qi;
    }

    while (--qi >= 0) {
        if (queues_n[qi] == n_values) {
            assert(nperms < P);

            for (int i = 0; i < n_values; ++i)
                permutations[nperms][i] = queues[qi][i];

            ++nperms;
        } else {
            int dequeued_i = qi;
            int dequeued_n = queues_n[dequeued_i];

            assert(dequeued_n < M);

            for (int op = 0; op < n_ops; ++op) {
                assert(qi < Q);

                for (int i = 0; i < dequeued_n; ++i) {
                    queues[qi][i] = queues[dequeued_i][i];
                }

                queues[qi][dequeued_n] = op;
                queues_n[qi] = dequeued_n + 1;

                ++qi;
            }
        }
    }

    return nperms;
}

static int64_t tens(int64_t num) {
    int64_t out = 1;

    do {
        num /= 10;
        out *= 10;
    } while (num > 0);

    return out;
}

static bool solvable(int i) {
    int iperm = nvalues[i] - 1;
    int nperms = npermutations[iperm];

    for (int p = 0; p < nperms; ++p) {
        int64_t res = values[i][0];

        for (int j = 1; j < nvalues[i]; ++j) {
            int op = permutations[iperm][p][j - 1];

            int64_t value = values[i][j];

            if (op == 0)      res += value;
            else if (op == 1) res *= value;
            else if (op == 2) res = (res * tens(value)) + value;
            else assert(false);

            if (res > results[i]) break;
        }

        if (res == results[i]) return true;
    }

    return false;
}

static bool solvable_part1(int i) {
    int perms = 1 << (nvalues[i] - 1);

    for (int p = 0; p < perms; ++p) {
        int64_t res = values[i][0];

        for (int j = 1; j < nvalues[i]; ++j) {
            int op = (p & (1 << (j - 1))) ? 1 : 0;

            int64_t value = values[i][j];

            if (op == 0) res += value;
            else if (op == 1) res *= value;
            else assert(false);

            if (res > results[i]) break;
        }

        if (res == results[i]) return true;
    }

    return false;
}

int main(void) {
    int parse_state = 0;

    int n_results = 0;
    int n_values = 0;
    int max_n_values = 0;

    while (!feof(stdin)) {
        if (parse_state == 0) {
            assert(n_results < N);
            assert(aoc_read_from_stdin_base10_s64(&results[n_results]));
            assert(aoc_read_from_stdin_char_and_chomp(':'));
            assert(aoc_read_from_stdin_char_and_chomp(' '));
            parse_state = 1;
        } else if (parse_state == 1) {
            assert(n_values < M);
            assert(aoc_read_from_stdin_base10_s64(&values[n_results][n_values++]));

            if (!aoc_read_from_stdin_char_and_chomp(' ')) {

                if (n_values > max_n_values) max_n_values = n_values;

                nvalues[n_results++] = n_values;
                n_values = 0;

                aoc_read_from_stdin_until_digit();
                parse_state = 0;
            }
        }
    }

    for (int i = 0; i < max_n_values; ++i)
        npermutations[i] = generate_permutations(3, i + 1, permutations[i]);

    int64_t sum = 0;

    for (int i = 0; i < n_results; ++i)
        if (solvable_part1(i)) sum += results[i];
        else  if (solvable(i))  sum += results[i];

    printf("%lld\n", sum);
    return 0;
}

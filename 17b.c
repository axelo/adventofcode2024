#include "aoc.h"

typedef struct {
    int64_t a;
    int64_t b;
    int64_t c;
    uint16_t pc;
} Computer;

#define combo(o) ((o) < 4 ? (o) : (o) == 4 ? c.a : (o) == 5 ? c.b : c.c)

#define N 16

static uint8_t program[N];
static uint8_t n_program;

static uint8_t run(int64_t a, uint8_t outputs[N]) {
    uint8_t n_outputs = 0;

    Computer c = {0};
    c.a = a;

    while (c.pc < n_program) {
        uint8_t opcode  = program[c.pc++];
        uint8_t operand = program[c.pc++];

        switch (opcode) {
        case 0: // adv
            c.a >>= combo(operand);
            break;

        case 1: // bxl
            c.b ^= operand;
            break;

        case 2: // bst
            c.b = combo(operand) & 7;
            break;

        case 3: // jnz
            if (c.a != 0) c.pc = operand;
            break;

        case 4: // bxc
            c.b ^= c.c;
            break;

        case 5: // out
            assert(n_outputs < 16);
            outputs[n_outputs++] = combo(operand) & 7;
            break;

        case 6: // bdv
            c.b = c.a >> combo(operand);
            break;

        case 7: // cdv
            c.c = c.a >> combo(operand);
            break;

        default: assert(false);
        }
    }

    return n_outputs;
}

static int64_t search_digit_backwards(int64_t a, int digit_i) {
    if (digit_i < 0) return a;

    int64_t step = (int64_t)1 << (3 * digit_i);
    int64_t end  = a + step * 7;

    uint8_t outputs[N];

    int64_t min_next_a = -1;

    for (; a <= end; a += step) {
        int n_outputs = run(a, outputs);

        if (digit_i < n_outputs) {
            if (outputs[digit_i] == program[digit_i]) {
                int64_t next_a = search_digit_backwards(a, digit_i - 1);

                if (next_a > 0 && ((min_next_a < 0) || (next_a < min_next_a)))
                    min_next_a = next_a;
            }
        }
    }

    return min_next_a;
}

int main(void) {
    assert(aoc_read_from_stdin_until_string_and_chomp("\n\nProgram: "));

    int instructions[33];
    int n = aoc_read_from_stdin_line(aoc_digit_to_int, 33, instructions);
    assert(n < 33);

    for (int i = 0; i < n; ++i) {
        if (instructions[i] >= 0 && instructions[i] <= 9) {
            assert(n_program < N);
            program[n_program++] = (uint8_t)instructions[i];
        }
    }

    int64_t a = search_digit_backwards(0, n_program - 1);

    printf("%lld\n", a);
    return 0;
}

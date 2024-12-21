#include "aoc.h"

#define N 16

typedef struct {
    int32_t a;
    int32_t b;
    int32_t c;
    uint16_t pc;
} Computer;

#define combo(o) ((o) < 4 ? (o) : (o) == 4 ? c.a : (o) == 5 ? c.b : c.c)

int main(void) {
    Computer c = {0};

    assert(aoc_read_from_stdin_string_and_chomp("Register A: "));
    assert(aoc_read_from_stdin_base10_s32_truncate(&c.a));
    assert(aoc_read_from_stdin_char_and_chomp('\n'));
    assert(aoc_read_from_stdin_string_and_chomp("Register B: "));
    assert(aoc_read_from_stdin_base10_s32_truncate(&c.b));
    assert(aoc_read_from_stdin_char_and_chomp('\n'));
    assert(aoc_read_from_stdin_string_and_chomp("Register C: "));
    assert(aoc_read_from_stdin_base10_s32_truncate(&c.c));
    assert(aoc_read_from_stdin_string_and_chomp("\n\nProgram: "));

    int instructions[33];
    int n = aoc_read_from_stdin_line(aoc_digit_to_int, 33, instructions);
    assert(n < 33);

    uint8_t program[N];
    uint8_t n_program = 0;

    for (int i = 0; i < n; ++i) {
        assert(n_program < N);
        if (instructions[i] >= 0 && instructions[i] <= 9) program[n_program++] = (uint8_t)instructions[i];
    }

    uint8_t outputs[N];
    int n_outputs = 0;

    while (c.pc < n_program) {
        uint8_t opcode = program[c.pc++];
        uint8_t operand = program[c.pc++];

        switch (opcode) {
        case 0:
            c.a >>= combo(operand);
            break;

        case 1:
            c.b ^= operand;
            break;

        case 2:
            c.b = combo(operand) & 7;
            break;

        case 3:
            if (c.a != 0) c.pc = operand;
            break;

        case 4:
            c.b ^= c.c;
            break;

        case 5:
            assert(n_outputs < N);
            outputs[n_outputs++] = combo(operand) & 7;
            break;

        case 6:
            c.b = c.a >> combo(operand);
            break;

        case 7:
            c.c = c.a >> combo(operand);
            break;

        default: assert(false);
        }
    }

    for (int i = 0; i < n_outputs; ++i) {
        if (i > 0) putchar(',');
        putchar(outputs[i] + '0');
    }
    putchar('\n');

    return 0;
}

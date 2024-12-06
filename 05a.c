#include "aoc.h"

#define MAX_PAGE 100
#define NPAGES 40

int npage_rules[MAX_PAGE] = {0};
int page_rules[MAX_PAGE][NPAGES];

#define NUPDATES 256
#define NUPDATED_PAGES 64

int nupdated_pages[NUPDATES] = {0};
int updates[NUPDATES][NUPDATED_PAGES];

static bool verify_page_updates(int ui) {
    for (int i = 1; i < nupdated_pages[ui]; ++i) {
        int page = updates[ui][i];

        for (int j = 0; j < npage_rules[page]; ++j) {
            int must_be_before_page = page_rules[page][j];

            for (int k = i - 1; k >= 0; --k) {
                int page_before = updates[ui][k];

                if (page_before == must_be_before_page) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main(void) {
    while (!feof(stdin)) {
        int64_t page1;
        int64_t page2;

        if (!aoc_read_from_stdin_base10_s64(&page1)) break;

        assert(aoc_read_from_stdin_char_and_chomp('|'));
        assert(aoc_read_from_stdin_base10_s64(&page2));
        assert(aoc_read_from_stdin_char_and_chomp('\n'));

        assert(page1 <= MAX_PAGE && page2 <= MAX_PAGE);

        int i = npage_rules[page1]++;
        assert(i < NPAGES);

        page_rules[page1][i] = (int)page2;
    }

    aoc_read_from_stdin_until_digit();

    int i = 0;
    int nu = 0;

    while (!feof(stdin)) {
        int64_t page;

        assert(aoc_read_from_stdin_base10_s64(&page));

        assert(i < NUPDATED_PAGES);
        updates[nu][i++] = (int)page;

        if (aoc_read_from_stdin_char_and_chomp(',')) continue;

        nupdated_pages[nu] = i;
        assert(++nu < NUPDATES);

        i = 0;

        aoc_read_from_stdin_until_digit();
    }

    int sum = 0;

    for (int ui = 0; ui < nu; ++ui)
        if (verify_page_updates(ui)) sum += updates[ui][nupdated_pages[ui] / 2];

    printf("%d\n", sum);
    return 0;
}

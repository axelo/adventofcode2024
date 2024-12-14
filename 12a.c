#include "aoc.h"

#define N 141

typedef struct {
    int area;
    int perim;
} Region;

static int map[N][N];

static Region plot_for(int size, int p, int x, int y, Region r) {
    int xl = x - 1;
    int xr = x + 1;
    int yu = y - 1;
    int yd = y + 1;

    map[y][x] = -p;

    if (xl < 0     || abs(map[y][xl]) != p) ++r.perim;
    if (xr >= size || abs(map[y][xr]) != p) ++r.perim;
    if (yu < 0     || abs(map[yu][x]) != p) ++r.perim;
    if (yd >= size || abs(map[yd][x]) != p) ++r.perim;

    r.area  += 1;

    if (xr < size && map[y][xr] == p)
        r = plot_for(size, p, xr, y, r);

    if (yd < size && map[yd][x] == p)
        r = plot_for(size, p, x, yd, r);

    if (xl >= 0 && map[y][xl] == p)
        r = plot_for(size, p, xl, y, r);

    if (yu >= 0 && map[yu][x] == p)
        r = plot_for(size, p, x, yu, r);

    return r;
}

int main(void) {
    int size = aoc_read_square_map_from_stdin(aoc_int_as_read, N, map);

    int price = 0;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (map[y][x] > 0) {
                Region r = plot_for(size, map[y][x], x, y, (Region){0});
                price += r.area * r.perim;
            }
        }
    }

    printf("%d\n", price);
    return 0;
}

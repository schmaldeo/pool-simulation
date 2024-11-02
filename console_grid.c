#include <math.h>
#include "console_grid.h"

#include <stdio.h>

// cartesian coordinates to grid coordinates
void map_to_grid(const point p, int *grid_x, int *grid_y, const int table_width, const int table_height) {
    *grid_x = (int)((p.x + table_width / 2) / table_width * CONSOLE_GRID_WIDTH);
    *grid_y = CONSOLE_GRID_HEIGHT - 1 - (int)((p.y + table_height / 2) / table_height * CONSOLE_GRID_HEIGHT);
}


// bresenham's line algorithm
void plot_line(grid g, int x0, int y0, int x1, int y1) {
    auto dx = abs(x1 - x0);
    auto sx = x0 < x1 ? 1 : -1;
    auto dy = -abs(y1 - y0);
    auto sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        if (x0 >= 0 && x0 < CONSOLE_GRID_WIDTH && y0 >= 0 && y0 < CONSOLE_GRID_HEIGHT) {
            g[y0][x0] = '*';
        }
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void print_grid(grid g) {
    printf("+");
    for (int i = 0; i < CONSOLE_GRID_WIDTH; i++) {
        printf("-");
    }
    printf("+\n");

    for (int i = 0; i < CONSOLE_GRID_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CONSOLE_GRID_WIDTH; j++) {
            putchar(g[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < CONSOLE_GRID_WIDTH; i++) {
        printf("-");
    }
    printf("+\n");
}

// fills grid with spaces
void initial_fill_grid(grid g) {
    for (int i = 0; i < CONSOLE_GRID_HEIGHT; i++) {
        for (int j = 0; j < CONSOLE_GRID_WIDTH; j++) {
            g[i][j] = ' ';
        }
    }
}

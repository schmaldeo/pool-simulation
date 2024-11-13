#include <stdio.h>
#include <math.h>
#include "console_grid.h"
#include "stb_ds.h"

// cartesian coordinates to grid coordinates
void map_to_grid(const point p, int *grid_x, int *grid_y, const long double table_width, const long double table_height) {
    *grid_x = (int)((p.x + table_width / 2) / table_width * CONSOLE_GRID_WIDTH);
    *grid_y = (int)((p.y + table_height / 2) / table_height * CONSOLE_GRID_HEIGHT);

    // make sure no bounces are outside the table
    if (*grid_x >= CONSOLE_GRID_WIDTH) {
        *grid_x = CONSOLE_GRID_WIDTH - 1;
    }

    if (*grid_y >= CONSOLE_GRID_HEIGHT) {
        *grid_y = CONSOLE_GRID_HEIGHT - 1;
    }

    // invert
    *grid_y = CONSOLE_GRID_HEIGHT - 1 - *grid_y;
}


// bresenham's line algorithm
void plot_line(grid g, int x0, int y0, const int x1, const int y1) {
    const auto dx = abs(x1 - x0);
    const auto sx = x0 < x1 ? 1 : -1;
    const auto dy = -abs(y1 - y0);
    const auto sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        if (x0 >= 0 && x0 < CONSOLE_GRID_WIDTH && y0 >= 0 && y0 < CONSOLE_GRID_HEIGHT) {
            g[y0][x0] = '*';
        }
        if (x0 == x1 && y0 == y1) break;
        const auto e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void mark_start_end(grid g, point *bounces, const long double table_width, const long double table_height) {
    int gx, gy;
    map_to_grid(bounces[0], &gx, &gy, table_width, table_height);
    if (gx >= 0 && gx < CONSOLE_GRID_WIDTH && gy >= 0 && gy < CONSOLE_GRID_HEIGHT) {
        g[gy][gx] = 'S';
    }

    map_to_grid(bounces[arrlen(bounces) - 1], &gx, &gy, table_width, table_height);
    if (gx >= 0 && gx < CONSOLE_GRID_WIDTH && gy >= 0 && gy < CONSOLE_GRID_HEIGHT) {
        g[gy][gx] = 'o';
    }
}

// fills grid with spaces
void initial_fill_grid(grid g) {
    for (int i = 0; i < CONSOLE_GRID_HEIGHT; i++) {
        for (int j = 0; j < CONSOLE_GRID_WIDTH; j++) {
            g[i][j] = ' ';
        }
    }
}

void plot_lines(grid g, point *bounces, const long double table_width, const long double table_height) {
    for (int i = 0; i < arrlen(bounces) - 1; i++) {
        int x0, y0, x1, y1;
        map_to_grid(bounces[i], &x0, &y0, table_width, table_height);
        map_to_grid(bounces[i + 1], &x1, &y1, table_width, table_height);

        plot_line(g, x0, y0, x1, y1);
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
            printf("%c", g[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < CONSOLE_GRID_WIDTH; i++) {
        printf("-");
    }
    printf("+\n");
}

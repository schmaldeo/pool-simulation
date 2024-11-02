#ifndef CONSOLE_GRID_H
#define CONSOLE_GRID_H

#include "geometry.h"

// odd values so there's a central point
#define CONSOLE_GRID_WIDTH 91
#define CONSOLE_GRID_HEIGHT 21

typedef char grid[CONSOLE_GRID_HEIGHT][CONSOLE_GRID_WIDTH];

void map_to_grid(const point p, int *grid_x, int *grid_y, const int table_width, const int table_height);
void plot_line(grid g, int x0, int y0, int x1, int y1);
void initial_fill_grid(grid g);
void print_grid(grid g);

#endif //CONSOLE_GRID_H

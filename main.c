#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "console_grid.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define BASE_TABLE_HEIGHT 2
#define BASE_TABLE_WIDTH 4
#define ENERGY_LOSS 0.95

// args:
// 1. m - table size multiplier (positive integer)
// 2. s - shot strength (positive integer)
// 3. x - X coordinate of the ball's initial placement (integer)
// 4. y - Y coordinate of the ball's initial placement (integer)
// 5. wx - X coordinate of vector of ball's initial movement
// 6. wy - Y coordinate of vector of ball's initial movement
int main(const int argc, char** argv) {
    setlocale(LC_CTYPE, "Polish");

    if (argc != 7) {
        wprintf(L"Program musi być uruchomiony z dokładnie sześcioma parametrami");
        return 1;
    }

    // parsing CLI arguments
    long double parsed_args[6];
    for (int i = 1; i < argc; i++) {
        char *endptr;
        const auto converted = strtold(argv[i], &endptr);

        // checking if the number can be parsed
        if (*endptr != '\0') {
            wprintf(L"Nieprawidłowy znak w argumencie nr %i.", i);
            return 1;
        }

        if (i == 1 && converted < 1) {
            wprintf(L"Parametr nr 1 musi być liczbą rzeczywistą większą bądź równą od 1.");
            return 1;
        }
        if (i == 2 && converted <= 0) {
            wprintf(L"Parametr nr 2 musi być liczbą rzeczywistą większą od zera.");
            return 1;
        }

        // check for ball out of bounds
        if (i == 3 && (converted > BASE_TABLE_WIDTH * parsed_args[0] / 2 || converted < BASE_TABLE_WIDTH * parsed_args[0] / 2 * -1)
            || i == 4 && (converted > BASE_TABLE_HEIGHT * parsed_args[0] / 2 || converted < BASE_TABLE_HEIGHT * parsed_args[0] / 2 * -1)) {
            wprintf(L"Położenie początkowe bili nie może być poza stołem.");
            return 1;
        }

        // check for [0, 0] vector
        if (i == 6 && converted == 0) {
            if (parsed_args[i - 2] == 0) {
                wprintf(L"Wektor nie może mieć wartości [0, 0].");
                return 1;
            }
        }

        parsed_args[i-1] = converted;
    }
    const auto table_size_multiplier = parsed_args[0];
    long double shot_strength = parsed_args[1];
    point a = {parsed_args[2], parsed_args[3]};
    const point vector = {parsed_args[4],  parsed_args[5]};
    const point b = {a.x + vector.x, a.y + vector.y};

    const auto length = BASE_TABLE_HEIGHT * table_size_multiplier;
    const auto width = BASE_TABLE_WIDTH * table_size_multiplier;

    char grid[CONSOLE_GRID_HEIGHT][CONSOLE_GRID_WIDTH];
    initial_fill_grid(grid);

    auto slope = (b.y - a.y) / (b.x - a.x);
    point out;
    bool positive[2] = {vector.y > 0, vector.x > 0};
    point *bounces = nullptr;
    arrpush(bounces, a);

    while (shot_strength > 0) {
        if (check_x_bounce(slope, length, width, positive[0], a, &out)) {
            const auto segment_length = calculate_segment_length(a, out);
            if (segment_length > shot_strength) {
                // because if the vector's x is 0, it's not a linear function, normal line calculations don't work
                // properly for it
                if (vector.x != 0.0) {
                    const auto p = calculate_segment_end(slope, a, shot_strength, positive[1], x);
                    arrpush(bounces, p);
                } else {
                    const point p = { out.x, positive[0] ? a.y + shot_strength : a.y - shot_strength };
                    arrpush(bounces, p);
                }
                break;
            }
            positive[0] = !positive[0];
        }

        if (check_y_bounce(slope, length, width, positive[1], a, &out)) {
            if (calculate_segment_length(a, out) > shot_strength) {
                const auto p = calculate_segment_end(slope, a, shot_strength, positive[1], x);
                arrpush(bounces, p);
                break;
            }
            positive[1] = !positive[1];
        }

        shot_strength -= calculate_segment_length(a, out);
        a = out;

        arrpush(bounces, a);

        shot_strength *= ENERGY_LOSS;
        slope *= -1;
    }

    // uncomment to print bounce coordinates
    // for (int i = 0; i < arrlen(bounces); i++) {
    //     printf("%Lf, %Lf\n", bounces[i].x, bounces[i].y);
    // }

    plot_lines(grid, bounces, width, length);
    mark_start_end(grid, bounces, width, length);
    print_grid(grid);

    arrfree(bounces);
    return 0;
}

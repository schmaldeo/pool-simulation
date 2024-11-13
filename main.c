#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "console_grid.h"
#include "simulation.h"

// args:
// 1. m - table size multiplier (positive integer)
// 2. s - shot strength (positive integer)
// 3. x - X coordinate of the ball's initial placement (integer)
// 4. y - Y coordinate of the ball's initial placement (integer)
// 5. wx - X coordinate of vector of ball's initial movement
// 6. wy - Y coordinate of vector of ball's initial movement
bool parse_args(const int argc, char** argv, simulation_args *out_parsed_args) {
    if (argc != 7) {
        wprintf(L"Program musi być uruchomiony z dokładnie sześcioma parametrami");
        return false;
    }

    long double parsed_arr[6];
    for (int i = 1; i < argc; i++) {
        char *endptr;
        const auto converted = strtold(argv[i], &endptr);

        // checking if the number can be parsed
        if (*endptr != '\0') {
            wprintf(L"Nieprawidłowy znak w argumencie nr %i.", i);
            return false;
        }

        if (i == 1 && converted < 1) {
            wprintf(L"Parametr nr 1 musi być liczbą rzeczywistą większą bądź równą od 1.");
            return false;
        }
        if (i == 2 && converted <= 0) {
            wprintf(L"Parametr nr 2 musi być liczbą rzeczywistą większą od zera.");
            return false;
        }

        // check for ball out of bounds
        if (i == 3 && (converted > BASE_TABLE_WIDTH * parsed_arr[0] / 2 || converted < BASE_TABLE_WIDTH * parsed_arr[0] / 2 * -1)
            || i == 4 && (converted > BASE_TABLE_HEIGHT * parsed_arr[0] / 2 || converted < BASE_TABLE_HEIGHT * parsed_arr[0] / 2 * -1)) {
            wprintf(L"Położenie początkowe bili nie może być poza stołem.");
            return false;
        }

        // check for [0, 0] vector
        if (i == 6 && converted == 0) {
            if (parsed_arr[i - 2] == 0) {
                wprintf(L"Wektor nie może mieć wartości [0, 0].");
                return false;
            }
        }

        parsed_arr[i-1] = converted;
    }
    out_parsed_args->shot_power = parsed_arr[1];
    const point a_point = { parsed_arr[2], parsed_arr[3] };
    const point vector = { parsed_arr[4], parsed_arr[5] };
    out_parsed_args->a = a_point;
    out_parsed_args->vector = vector;
    out_parsed_args->table_width = BASE_TABLE_WIDTH * parsed_arr[0];
    out_parsed_args->table_height = BASE_TABLE_HEIGHT * parsed_arr[0];
    return true;
}

int main(const int argc, char** argv) {
    setlocale(LC_CTYPE, "Polish");

    char grid[CONSOLE_GRID_HEIGHT][CONSOLE_GRID_WIDTH];
    initial_fill_grid(grid);

    simulation_args parsed_args;
    if (!parse_args(argc, argv, &parsed_args)) return 1;
    point* bounces = nullptr;
    bounces = run_simulation(parsed_args, bounces);

    // uncomment to print bounce coordinates
    // for (int i = 0; i < arrlen(bounces); i++) {
    //     printf("%Lf, %Lf\n", bounces[i].x, bounces[i].y);
    // }

    print_grid(grid, bounces, parsed_args.table_width, parsed_args.table_height);
    cleanup(bounces);

    return 0;
}

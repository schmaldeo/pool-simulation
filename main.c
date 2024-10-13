#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_TABLE_LENGTH 2
#define BASE_TABLE_WIDTH 4

typedef struct { long long x; long long y; } point;

// args:
// 1. m - table size multiplier (positive integer)
// 2. s - shot strength (positive integer)
// 3. x - X coordinate of the ball's initial placement (integer)
// 4. y - Y coordinate of the ball's initial placement (integer)
// 5. wx - X coordinate of vector of ball's initial movement
// 6. wy - Y coordinate of vector of ball's initial movement
int main(int argc, char** argv) {
    setlocale(LC_ALL, "Polish");

    if (argc != 7) {
        wprintf(L"Program musi być uruchomiony z dokładnie sześcioma parametrami");
        return 1;
    }

    // parsing CLI arguments
    long long parsed_args[6];
    for (int i = 1; i < argc; i++) {
        char *endptr;
        auto converted = _strtoi64(argv[i], &endptr, 10);

        // checking if the number can be parsed
        if (*endptr != '\0') {
            wprintf(L"Nieprawidłowy znak w argumencie nr %i.", i);
            return 1;
        }

        // parsing first two parameters, as they should be positive integers
        if ((i == 1 || i == 2) && converted < 1) {
            wprintf(L"Parametry nr 1 i 2 powinny być dodatnimi liczbami całkowitymi.");
            return 1;
        }

        // printf("%lli\n", converted);

        parsed_args[i-1] = converted;
    }
    const auto table_size_multiplier = parsed_args[0];
    const auto shot_strength = parsed_args[1];
    const point initial_ball = {parsed_args[2], parsed_args[3]};
    const point vector = {parsed_args[4], parsed_args[5]};

    auto length = BASE_TABLE_LENGTH * table_size_multiplier;
    auto width = BASE_TABLE_WIDTH * table_size_multiplier;

    return 0;
}

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_TABLE_LENGTH 2
#define BASE_TABLE_WIDTH 4

typedef struct { long double x; long double y; } point;

// checks if there is a bounce off the boundary along the Y axis
bool check_y_bounce(const long double a, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point) {
    auto x = table_width / 2;
    // if checking bottom boundary
    if (!positive) x *= -1;
    const auto y = a * x - in_point.x * a + in_point.y;

    const auto height = table_height / 2;
    if (y <= height && y >= -height) {
        out_point->x = x;
        out_point->y = y;
        return true;
    }
    return false;
}

bool check_x_bounce(const long double a, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point) {
    auto y = table_height / 2;
    if (!positive) y *= -1;
    const auto x = (y - in_point.y) / a + in_point.x;
    const auto width = table_width / 2;

    if (x <= width && x >= -width) {
        out_point->x = x;
        out_point->y = y;
        return true;
    }
    return false;
}

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
        const auto converted = _strtoi64(argv[i], &endptr, 10);

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

        // TODO parse initial position to see if it's within table bounds

        // printf("%lli\n", converted);

        parsed_args[i-1] = converted;
    }
    const auto table_size_multiplier = parsed_args[0];
    const long double shot_strength = (long double)parsed_args[1];
    point a = {(long double)parsed_args[2], (long double)parsed_args[3]};
    const point vector = {(long double)parsed_args[4], (long double) parsed_args[5]};
    const point b = {a.x + vector.x, a.y + vector.y};

    auto length = BASE_TABLE_LENGTH * table_size_multiplier;
    auto width = BASE_TABLE_WIDTH * table_size_multiplier;

    // const point new = {-6, -1};
    // if (check_x_bounce(-3.0/2, 6, 12, false, new, &out)) {
    //     printf("true");
    // } else {
    //     printf("false");
    // }

    auto a_multiplier = (b.y - a.y) / (b.x - a.x);

    int i = 0;
    point out;
    bool positive[2] = {vector.x > 0, vector.y > 0};
    while (i < 5) {
        if (check_x_bounce(a_multiplier, length, width, positive[0], a, &out)) {
            positive[0] = !positive[0];
            a = out;
        }

        if (check_y_bounce(a_multiplier, length, width, positive[1], a, &out)) {
            positive[1] = !positive[1];
            a = out;
        }

        printf("%Lf, %Lf\n", a.x, a.y);

        a_multiplier *= -1;
        i++;
    }

    return 0;
}

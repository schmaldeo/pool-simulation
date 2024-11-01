#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_TABLE_HEIGHT 2
#define BASE_TABLE_WIDTH 4
#define ENERGY_LOSS 0.95

// print

typedef struct { long double x; long double y; } point;

// checks if there is a bounce off the boundary along the Y axis
bool check_y_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point) {
    auto x = table_width / 2;
    // if checking bottom boundary
    if (!positive) x *= -1;
    const auto y = slope * x - in_point.x * slope + in_point.y;

    const auto height = table_height / 2;
    if (y <= height && y >= -height) {
        out_point->x = x;
        out_point->y = y;
        return true;
    }
    return false;
}

bool check_x_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point) {
    auto y = table_height / 2;
    if (!positive) y *= -1;
    const auto x = (y - in_point.y) / slope + in_point.x;

    const auto width = table_width / 2;
    if (x <= width && x >= -width) {
        out_point->x = x;
        out_point->y = y;
        return true;
    }
    return false;
}

long double calculate_segment_length(const point a, const point b) {
    return sqrtl(powl(b.x - a.x, 2.0) + powl(b.y - a.y, 2.0));
}

// TODO working correctly but still need to know if it's going positive or negative atm
bool calculate_segment_end(const long double slope, const point p, const long double length, bool positive, const int table_height, const int table_width, point *out_point) {
    auto a = powl(slope, 2.0) + 1;
    auto b = -2 * p.x - 2 * p.x * powl(slope, 2.0);
    auto c = powl(p.x, 2.0) + powl(slope * p.x, 2.0) - powl(length, 2.0);

    auto delta = powl(b, 2.0) - (4 * a * c);
    auto delta_sqrt = sqrtl(delta);
    auto xb1 = (-b - delta_sqrt) / (2 * a);
    auto xb2 = (-b + delta_sqrt) / (2 * a);

    auto yb1 = (slope * xb1) - (slope * p.x) + p.y;
    auto yb2 = (slope * xb2) - (slope * p.x) + p.y;

    // both points are valid, just on a different side of the point that's passed to the function
    if (positive
        && xb2 <= table_width / 2.0 && xb2 >= -(table_width / 2.0)
        && yb2 <= table_height / 2.0 && yb2 >= -(table_height / 2.0)) {
        out_point->x = xb2;
        out_point->y = yb2;
        return true;
    }

    if (!positive
        && xb1 <= table_width / 2.0 && xb1 >= -(table_width / 2.0)
        && yb1 <= table_height / 2.0 && yb1 >= -(table_height / 2.0)) {
        out_point->x = xb1;
        out_point->y = yb1;
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
    long double shot_strength = (long double)parsed_args[1];
    point a = {(long double)parsed_args[2], (long double)parsed_args[3]};
    const point vector = {(long double)parsed_args[4], (long double) parsed_args[5]};
    const point b = {a.x + vector.x, a.y + vector.y};

    const auto length = BASE_TABLE_HEIGHT * table_size_multiplier;
    const auto width = BASE_TABLE_WIDTH * table_size_multiplier;

    // TODO 0 div
    auto slope = (b.y - a.y) / (b.x - a.x);
    point out;
    bool positive[2] = {vector.x > 0, vector.y > 0};
    while (shot_strength > 0) {
        if (check_x_bounce(slope, length, width, positive[0], a, &out)) {
            if (calculate_segment_length(a, out) > shot_strength) {
                calculate_segment_end(slope, a, shot_strength, positive[0], length, width, &out);
                printf("stopped at %Lf, %Lf", out.x, out.y);
                break;
            }
            positive[0] = !positive[0];
        }

        if (check_y_bounce(slope, length, width, positive[1], a, &out)) {
            if (calculate_segment_length(a, out) > shot_strength) {
                calculate_segment_end(slope, a, shot_strength, positive[1], length, width, &out);
                printf("stopped at %Lf, %Lf", out.x, out.y);
                break;
            }
            positive[1] = !positive[1];
        }

        shot_strength -= calculate_segment_length(a, out);
        a = out;

        printf("%Lf, %Lf, %Lf\n", a.x, a.y, shot_strength);

        shot_strength *= ENERGY_LOSS;
        slope *= -1;
    }

    return 0;
}

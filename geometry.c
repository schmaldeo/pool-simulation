#include <math.h>
#include "geometry.h"
#include "simulation.h"

// checks if there is a bounce off the boundary along the Y axis
bool check_y_bounce(const long double slope, const long double table_width, const long double table_height, const bool positive, const point in_point, point *out_point) {
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

bool check_x_bounce(const long double slope, const long double table_width, const long double table_height, const bool positive, const point in_point, point *out_point) {
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

point calculate_segment_end(const long double slope, const point p, const long double length, const bool positive, const axis axis) {
    const auto a = powl(slope, 2.0) + 1;
    const auto b = -2 * p.x - 2 * p.x * powl(slope, 2.0);
    const auto c = powl(p.x, 2.0) + powl(slope * p.x, 2.0) - powl(length, 2.0);

    const auto delta = powl(b, 2.0) - 4 * a * c;
    const auto delta_sqrt = sqrtl(delta);
    const auto xb1 = (-b - delta_sqrt) / (2 * a);
    const auto xb2 = (-b + delta_sqrt) / (2 * a);

    const auto yb1 = slope * xb1 - slope * p.x + p.y;
    const auto yb2 = slope * xb2 - slope * p.x + p.y;

    // both points are valid, just on a different side of the point that's passed to the function
    if ((axis == x && positive)
        || (axis == y && ((positive && slope > 0) || (!positive && slope < 0)))) {
        const point stop = { xb2, yb2 };
        return stop;
    }
    const point stop = { xb1, yb1 };
    return stop;
}

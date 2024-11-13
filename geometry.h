#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "simulation.h"

typedef enum { x, y } axis;

bool check_y_bounce(long double slope, long double table_height, long double table_width, bool positive, point in_point, point *out_point);
bool check_x_bounce(long double slope, long double table_height, long double table_width, bool positive, point in_point, point *out_point);
long double calculate_segment_length(point a, point b);
point calculate_segment_end(long double slope, point p, long double length, bool positive, axis axis);


#endif //GEOMETRY_H

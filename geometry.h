#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct { long double x; long double y; } point;

typedef enum { x, y } axis;

bool check_y_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point);
bool check_x_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point);
long double calculate_segment_length(const point a, const point b);
point calculate_segment_end(const long double slope, const point p, const long double length, bool positive, axis axis);


#endif //GEOMETRY_H

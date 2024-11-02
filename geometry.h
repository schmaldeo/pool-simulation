#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct { long double x; long double y; } point;

bool check_y_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point);
bool check_x_bounce(const long double slope, const int table_height, const int table_width, const bool positive, const point in_point, point *out_point);
long double calculate_segment_length(const point a, const point b);
bool calculate_segment_end(const long double slope, const point p, const long double length, bool positive, const int table_height, const int table_width, point *out_point);


#endif //GEOMETRY_H

#ifndef SIMULATION_H
#define SIMULATION_H

#define BASE_TABLE_HEIGHT 2
#define BASE_TABLE_WIDTH 4
#define ENERGY_LOSS 0.95

// this is defined here rather than in geometry.h, because they depend on each other anyway,
// however if point were defined in geometry, end user would have to include both headers, while if it's like this,
// only simulation.h is needed
typedef struct { long double x; long double y; } point;

typedef struct {
    point a;
    point vector;
    long double shot_power;
    long double table_width;
    long double table_height;
} simulation_args;

point* run_simulation(simulation_args args, point *bounces);
void cleanup(point *bounces);

#endif //SIMULATION_H

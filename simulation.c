#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "simulation.h"
#include "geometry.h"

point* run_simulation(const simulation_args args, point *bounces) {
    // the parsing probably should be done in main.c and the values shouldn't be copied to variables
    point a = args.a;
    long double shot_power = args.shot_power;
    auto slope = args.vector.y / args.vector.x;
    point out;
    bool positive[2] = {args.vector.y > 0, args.vector.x > 0};
    arrpush(bounces, a);

    while (shot_power > 0) {
        if (check_x_bounce(slope, args.table_width, args.table_height, positive[0], a, &out)) {
            const auto segment_length = calculate_segment_length(a, out);
            if (segment_length > shot_power) {
                // because if the vector's x is 0, it's not a linear function, normal line calculations don't work
                // properly for it
                if (args.vector.x != 0.0) {
                    const auto p = calculate_segment_end(slope, a, shot_power, positive[1], x);
                    arrpush(bounces, p);
                } else {
                    const point p = { out.x, positive[0] ? a.y + shot_power : a.y - shot_power };
                    arrpush(bounces, p);
                }
                break;
            }
            positive[0] = !positive[0];
        }

        if (check_y_bounce(slope, args.table_width, args.table_height, positive[1], a, &out)) {
            if (calculate_segment_length(a, out) > shot_power) {
                const auto p = calculate_segment_end(slope, a, shot_power, positive[1], x);
                arrpush(bounces, p);
                break;
            }
            positive[1] = !positive[1];
        }

        shot_power -= calculate_segment_length(a, out);
        a = out;

        arrpush(bounces, a);

        shot_power *= ENERGY_LOSS;
        slope *= -1;
    }

    return bounces;
}

void cleanup(point *bounces) {
    arrfree(bounces);
}
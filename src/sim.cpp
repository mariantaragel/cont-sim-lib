#include "sim.hpp"

double t, t_start, t_end, h;
const char *out_file;

void set_simtime(double start, double end) {
    t_start = start;
    t_end = end;
}

void set_output(const char *file) {
    out_file = file;
}

void set_stepsize(double step) {
    h = step;
}

#include <fstream>
#include <iostream>
#include <cmath>
#include "sim.hpp"

double t, t_start, t_end;
const char *out_file;

void set_simtime(double start, double end) {
    t_start = start;
    t_end = end;
}

void set_output(const char *file) {
    out_file = file;
}

void start_simulation(std::function<std::vector<double>(double, std::vector<double>)> system, std::vector<double> y, ODEsolver &solver)
{
    t = 0.0;

    std::ofstream file(out_file);
    file << t << " " << y[0] << " " << y[1] << std::endl;

    while (t < t_end) {
        y = solver.step(system, t, y);

        file << t << " " << y[0] << " " << y[1] << std::endl;
    }

    file.close();
    std::cout << "Dáta uložené do " << out_file << std::endl;
}

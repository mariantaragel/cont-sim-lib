#ifndef SIM_HPP
#define SIM_HPP

#include <vector>
#include <functional>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include "ode.hpp"
#include "euler.hpp"
#include "rk4.hpp"
#include "ab4.hpp"
#include "integrator.hpp"

extern double t, t_start, t_end, h;
extern const char *out_file;

void set_simtime(double start, double end);
void set_output(const char *file);
void set_stepsize(double step);

template <typename Model>
void start_simulation(Model &model);

template <typename Model>
void print_values(std::ofstream &file, Model &model, double &t);

template <typename Model>
inline void start_simulation(Model &model)
{
    t = t_start;
    std::ofstream file(out_file);

    while (t <= t_end) {
        print_values(file, model, t);
        model.step(t, h);
        t += h;
    }

    file.close();
    std::cout << "Dáta uložené do " << out_file << std::endl;
}

template <typename Model>
inline void print_values(std::ofstream &file, Model &model, double &t)
{
    std::vector<double> y = model.output();
    file << t;
    for (auto v : y)
        file << " " << v;
    file << " " << std::cos(t);
    file << " " << std::sin(t);
    file << std::endl;
}

#endif
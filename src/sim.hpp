#ifndef SIM_HPP
#define SIM_HPP

#include <vector>
#include <functional>
#include <cstdlib>
#include "ode.hpp"
#include "rk4.hpp"
#include "euler.hpp"

void set_simtime(double start, double end);
void set_output(const char *file);
void start_simulation(std::function<std::vector<double>(double, std::vector<double>)> system, std::vector<double> y, ODEsolver &solver);

#endif

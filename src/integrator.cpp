#include "integrator.hpp"

Integrator::Integrator(std::function<double(double, std::vector<double>)> df,
                       double initial_value)
    : f(df), value(initial_value) {}

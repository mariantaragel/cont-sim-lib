#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <functional>
#include <vector>

class Integrator {
public:
    Integrator(std::function<double(double, std::vector<double>)> df,
               double initial_value);
    std::function<double(double, std::vector<double>)> f;
    double value;
};

#endif
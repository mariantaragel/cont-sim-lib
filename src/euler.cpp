#include "euler.hpp"

void Euler::step(double &t, double &h, std::vector<Integrator*> &integrators)
{
    size_t size = integrators.size();
    std::vector<double> y_values(size);
    std::vector<double> k(size);

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        y_values[i] = y->value;
    }
    
    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        k[i] = h * y->f(t, y_values);
    }

    for (size_t i = 0; i < size; i++) {
        integrators[i]->value += k[i];
    }
}
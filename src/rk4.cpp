#include "rk4.hpp"
#include <iostream>

void RungeKutta4::step(double &t, double &h, std::vector<Integrator*> &integrators)
{
    size_t size = integrators.size();
    std::vector<double> y_values(size);
    std::vector<double> k1(size), k2(size), k3(size), k4(size);
    
    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        y_values[i] = y->value;
    }

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        k1[i] = y->f(t, y_values);
    }

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        k2[i] = y->f(t + h / 2, vec_sum(y_values, vec_scale(k1, h / 2.0)));
    }

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        k3[i] = y->f(t + h / 2, vec_sum(y_values, vec_scale(k2, h / 2.0)));
    }

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        k4[i] = y->f(t + h, vec_sum(y_values, vec_scale(k3, h)));
    }

    for (size_t i = 0; i < size; i++) {
        integrators[i]->value += h * (k1[i] / 6 + k2[i] / 3 + k3[i] / 3 + k4[i] / 6);
    }
}

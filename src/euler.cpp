#include "euler.hpp"

Euler::Euler(double step) : ODEsolver(step) {}

std::vector<double> Euler::step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y)
{
    std::vector<double> k = vec_scale(f(t, y), h);

    std::vector<double> y_n(y.size());
    for (size_t i = 0; i < y_n.size(); i++) {
        y_n[i] = y[i] + k[i];
    }

    t += h;
    return y_n;
}
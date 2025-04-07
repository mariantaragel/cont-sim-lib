#include "rk4.hpp"

RungeKutta4::RungeKutta4(double step) : ODEsolver(step) {}

std::vector<double> RungeKutta4::step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y)
{
    std::vector<double> k1 = f(t, y);
    std::vector<double> k2 = f(t + h / 2, vec_sum(y, vec_scale(k1, h / 2)));
    std::vector<double> k3 = f(t + h / 2, vec_sum(y, vec_scale(k2, h / 2)));
    std::vector<double> k4 = f(t + h, vec_sum(y, vec_scale(k3, h)));

    std::vector<double> y_n(y.size());
    for (size_t i = 0; i < y.size(); ++i) {
        y_n[i] = y[i] + (h / 6.0) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
    }

    t += h;
    return y_n;
}

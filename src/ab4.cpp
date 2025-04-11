#include "ab4.hpp"

AdamsBashforth4::AdamsBashforth4(double step) : ODEsolver(step), rk4_solver(step), fi(4) {}

std::vector<double> AdamsBashforth4::step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y)
{
    fi[p] = f(t, y);
    
    if (n < 4) {
        ++n;
        p = (p + 1) % 4;
        return rk4_solver.step(f, t, y);
    }

    std::vector<double> y_n(y.size());
    for (size_t i = 0; i < y.size(); ++i) {
        y_n[i] = y[i] + (h / 24.0) * (
            55 * fi[(p + 0) % 4][i] -
            59 * fi[(p + 3) % 4][i] +
            37 * fi[(p + 2) % 4][i] -
            9 * fi[(p + 1) % 4][i]
        );
    }
    
    ++n;
    p = (p + 1) % 4;
    t += h;
    return y_n;
}

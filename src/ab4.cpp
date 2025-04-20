#include "ab4.hpp"

AdamsBashforth4::AdamsBashforth4() : fi(4)
{
    rk4_solver = RungeKutta4();
}

void AdamsBashforth4::step(double &t, double &h, std::vector<Integrator*> &integrators)
{
    size_t size = integrators.size();
    std::vector<double> y_values(size);
    std::vector<double> f_curr(size);

    for (size_t i = 0; i < size; i++) {
        Integrator *y = integrators[i];
        y_values[i] = y->value;
    }

    for (size_t i = 0; i < size; i++) {
        f_curr[i] = integrators[i]->f(t, y_values);
    }

    if (n < 4) {
        rk4_solver.step(t, h, integrators);
        fi[p] = f_curr;
        p = (p + 1) % 4;
        ++n;
        return;
    }

    fi[p] = f_curr;

    for (size_t i = 0; i < size; ++i) {
        integrators[i]->value += (h / 24.0) * (
            55.0 * fi[(p + 0) % 4][i] -
            59.0 * fi[(p + 3) % 4][i] +
            37.0 * fi[(p + 2) % 4][i] -
             9.0 * fi[(p + 1) % 4][i]
        );
    }
    
    p = (p + 1) % 4;
    ++n;
}

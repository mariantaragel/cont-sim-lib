#ifndef AB4_HPP
#define AB4_HPP

#include "ode.hpp"
#include "rk4.hpp"

class AdamsBashforth4 :ODEsolver {
public:
    AdamsBashforth4();
    void step(double &t, double &h, std::vector<Integrator*> &integrators) override;

private:
    unsigned n = 0;
    unsigned p = 0;
    RungeKutta4 rk4_solver;
    std::vector<std::vector<double>> fi;
};


#endif
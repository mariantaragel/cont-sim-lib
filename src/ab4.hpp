#ifndef AB4_HPP
#define AB4_HPP

#include "ode.hpp"
#include "rk4.hpp"

class AdamsBashforth4 : public ODEsolver {
public:
    AdamsBashforth4(double step);
    std::vector<double> step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y) override;

private:
    unsigned n = 0;
    unsigned p = 0;
    RungeKutta4 rk4_solver;
    std::vector<std::vector<double>> fi;
};

#endif
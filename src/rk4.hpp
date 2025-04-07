#ifndef RK4_HPP
#define RK4_HPP

#include "ode.hpp"

class RungeKutta4 : public ODEsolver {
public:
    RungeKutta4(double step);
    std::vector<double> step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y) override;
};

#endif

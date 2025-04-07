#ifndef EULER_HPP
#define EULER_HPP

#include "ode.hpp"

class Euler : public ODEsolver {
public:
    Euler(double step);
    std::vector<double> step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y) override;
};

#endif

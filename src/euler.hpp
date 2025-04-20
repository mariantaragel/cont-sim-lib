#ifndef EULER_HPP
#define EULER_HPP

#include "ode.hpp"

class Euler : public ODEsolver {
public:
    Euler() {};
    void step(double &t, double &h, std::vector<Integrator*> &integrators) override;
};

#endif

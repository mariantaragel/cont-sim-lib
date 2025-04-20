#ifndef RK4_HPP
#define RK4_HPP

#include "ode.hpp"

class RungeKutta4 : public ODEsolver{
public:
    RungeKutta4() {};
    void step(double &t, double &h, std::vector<Integrator*> &integrators) override;
};

#endif

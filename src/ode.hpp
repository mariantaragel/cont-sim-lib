#ifndef ODE_HPP
#define ODE_HPP

#include <vector>
#include <cstdio>
#include <functional>
#include "integrator.hpp"

class ODEsolver {
public:
    ODEsolver() {};
    virtual void step(double &t, double &h, std::vector<Integrator*> &integrators);
protected:
    static std::vector<double> vec_sum(const std::vector<double> &vec1, const std::vector<double> &vec2);
    static std::vector<double> vec_scale(const std::vector<double> &vec, double k);
};

#endif
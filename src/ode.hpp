#ifndef ODE_HPP
#define ODE_HPP

#include <vector>
#include <cstdio>
#include <functional>

class ODEsolver {
public:
    ODEsolver(double step) : h(step) {};
    virtual std::vector<double> step(std::function<std::vector<double>(double, std::vector<double>)> f, double &t, std::vector<double> &y);
protected:
    double h;
    static std::vector<double> vec_sum(const std::vector<double> &v1, const std::vector<double> &v2);
    static std::vector<double> vec_scale(const std::vector<double> &v, double k);
};

#endif
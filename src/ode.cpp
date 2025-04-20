#include "ode.hpp"

void ODEsolver::step(double &t, double &h, std::vector<Integrator*> &integrators)
{
}

std::vector<double> ODEsolver::vec_sum(const std::vector<double> &vec1, const std::vector<double> &vec2)
{
    std::vector<double> result(vec1.size());
    for (size_t i = 0; i < vec1.size(); i++) {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

std::vector<double> ODEsolver::vec_scale(const std::vector<double> &vec, double c) {
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); i++) {
        result[i] = c * vec[i];
    }
    return result;
}

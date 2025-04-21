#include "sim.hpp"

int main()
{
    struct EnzymeModel {
        Integrator s, e, p;
        std::vector<Integrator*> integrators;
        RungeKutta4 solver;

        const double k = 1.0;
        const double tau = 0.5;

        EnzymeModel(double s0, double e0, double p0) :
            s([&](double t, std::vector<double> y) {
                double s = y[0]; double e = y[1];
                return -k * e * s; }, s0),
            e([&](double t, std::vector<double> y) {
                double s = y[0]; double e = y[1];
                return -k * e * s + k * e * s; }, e0),
            p([&](double t, std::vector<double> y) {
                double s = y[0]; double e = y[1];
                return  k * e * s; }, p0)
            {
                integrators = {&s, &e, &p};
            }

        void step(double &t, double &h) {
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {s.value, e.value, p.value};
        }
    };

    EnzymeModel model(1.0, 0.9, 0.0);

    set_stepsize(0.01);
    set_simtime(0.0, 5.0);
    set_output("simulation_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
#include "sim.hpp"

int main()
{
    struct HIVModel {
        Integrator dIE, dI, dV, dT;
        std::vector<Integrator*> integrators;
        RungeKutta4 solver;

        // const double beta = 4.8e-6, lambda = 2.3;
        // const double deltaIE = 0.05, deltaI = 0.24;
        // const double N = 500, C = 3;
        // const double m = 2.475, mi0 = 0.0046;

        const double beta = 4.8e-6, lambda = 23;
        const double deltaIE = 0.05, deltaI = 0.2;
        const double N = 500, C = 2.4;
        const double m = 2.475, mi0 = 0.0046;

        HIVModel(double dIE0, double dI0, double dV0, double dT0) :
            dIE([&](double t, std::vector<double> y) {
                double IE = y[0], V = y[2], T = y[3];
                return beta * T * V - (m + deltaIE) * IE; }, dIE0),
            dI([&](double t, std::vector<double> y) {
                double IE = y[0], I = y[1];
                return m * IE - deltaI * I; }, dI0),
            dV([&](double t, std::vector<double> y) {
                double I = y[1], V = y[2], T = y[3];
                return N * deltaI * I - C * V - beta * T * V; }, dV0),
            dT([&](double t, std::vector<double> y) {
                double V = y[2], T = y[3];
                return lambda - beta * T * V - mi0 * T; }, dT0)
            {
                integrators = {&dIE, &dI, &dV, &dT};
            }

        void step(double &t, double &h) {
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {dIE.value, dI.value, dV.value, dT.value};
        }
    };

    HIVModel model(1.0, 1.0, 1.0, 100.0);

    set_stepsize(0.001);
    set_simtime(0.0, 600.0);
    set_output("simulation_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
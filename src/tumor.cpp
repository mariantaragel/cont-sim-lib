#include "sim.hpp"

int main()
{
    struct TumorModel {
        Integrator dTI, dTM, dI;
        std::vector<Integrator*> integrators;
        RungeKutta4 solver;

        const double a1 = 0.8470, a4 = 0.9159;
        const double c1 = 7.56e-2, c2 = 3.422e-4, c3 = 7.56e-2, c4 = 3.422e-4;
        const double d1 = 0.04, d2 = 0.1145, d3 = 0.6641;
        const double k = 0.037, rho = 0.2, alpha = 0.3e6, n = 3;

        TumorModel(double dTI0, double dTM0, double dI0) :
            dTI([&](double t, std::vector<double> y) {
                double TI = y[0], TM = y[1], I = y[2];
                return 2 * a4 * TM - (c1 * I + d2) * TI - a1 * TI; }, dTI0),
            dTM([&](double t, std::vector<double> y) {
                double TI = y[0], TM = y[1], I = y[2];
                return a1 * TI - d3 * TM - a4 * TM - c3 * TM * I; }, dTM0),
            dI([&](double t, std::vector<double> y) {
                double TI = y[0], TM = y[1], I = y[2];
                return k + (rho * I * pow(TI + TM, n)) / (alpha + pow(TI + TM, n)) - c2 * I * TI - c4 * TM * I - d1 * I; }, dI0)
            {
                integrators = {&dTI, &dTM, &dI};
            }

        void step(double &t, double &h) {
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {dTI.value, dTM.value, dI.value};
        }
    };

    TumorModel model(1.0, 1.0, 0.0);

    set_stepsize(0.01);
    set_simtime(0.0, 100.0);
    set_output("simulation_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
#include "sim.hpp"

int main()
{
    struct TankModel {
        Integrator dil, domegal, dFl, dir, domegar, dFr;
        std::vector<Integrator*> integrators;
        RungeKutta4 solver;

        double const el, er;
        double const vl, vr;
        double const Lm = 10e-3, Rm = 3.1;
        double const alpha = 10e-3;
        double const Bg = 6.7e-7, Jg = 1.2e-6, Kt = 10e-3;
        double const g = 204, r = 0.015;

        TankModel(double dil0, double domegal0, double dFl0, double dir0, double domegar0, double dFr0) :
            dil([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Lm * (el - il * Rm - alpha * omegal); }, dil0),
            domegal([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Jg * (alpha * il - omegal * Bg - r / g * Fl); }, domegal0),
            dFl([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Kt * (r / g * omegal - vl); }, dFl0),
            dir([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Lm * (er - ir * Rm - alpha * omegar); }, dir0),
            domegar([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Jg * (alpha * ir - omegar * Bg - r / g * Fr); }, domegar0),
            dFr([&](double t, std::vector<double> y) {
                double il = y[0], omegal = y[1], Fl = y[2], ir = y[3], omegar = y[4], Fr = y[5];
                return 1 / Kt * (r / g * omegar - vr); }, dFr0)
            {
                integrators = {&dil, &domegal, &dFl, &dir, &domegar, &dFr};
            }

        void step(double &t, double &h) {
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {dil.value, domegal.value, dFl.value, dir.value, domegar.value, dFr.value};
        }
    };

    TankModel model(1.0, 1.0, 1.0, 100.0, 0.0, 0.0);

    set_stepsize(0.001);
    set_simtime(0.0, 600.0);
    set_output("simulation_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
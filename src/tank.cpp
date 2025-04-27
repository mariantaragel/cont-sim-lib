#include "sim.hpp"

int main()
{
    struct TankModel {
        Integrator dv, domega, dtheta, dx, dy;
        std::vector<Integrator*> integrators;
        RungeKutta4 solver;

        bool turning = true;
        double const Sl = 0.3;
        double const Fl = 8.0, Fr = 1.0;
        double const Br = 1.0, Bl = 0.7, Bs = 14.0, Jt = 5e-4;
        double const mt = 0.8, B = 0.1;

        TankModel(double v0, double omega0, double theta0, double x0, double y0) :
            dv([&](double t, std::vector<double> yv) {
                double v = yv[0];
                if (turning) {
                    return 1.0 / mt * (Fl + Fr - (Br + Bs) * v);
                } else {
                    return 1.0 / mt * (Fl + Fr - Br * v);
                }
                }, v0),
            domega([&](double t, std::vector<double> yv) {
                double omega = yv[1];
                if (turning) {
                    return 1 / Jt * (B / 2.0 * (Fl - Fr) - Bl * omega);
                } else {
                    return 0.0;
                }
                }, omega0),
            dtheta([&](double t, std::vector<double> yv) {
                double omega = yv[1];
                return omega; }, theta0),
            dx([&](double t, std::vector<double> yv) {
                double v = yv[0], theta = yv[2];
                return v * std::sin(theta); }, x0),
            dy([&](double t, std::vector<double> yv) {
                double v = yv[0], theta = yv[2];
                return v * std::cos(theta); }, y0)
            {
                integrators = {&dv, &domega, &dtheta, &dx, &dy};
            }

        void step(double &t, double &h) {
            turning = (B / 2.0 * std::abs(Fl - Fr)) >= Sl;
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {dv.value, domega.value, dtheta.value, dx.value, dy.value};
        }
    };

    TankModel model(0.0, 0.0, 0.0, 0.0, 0.0);

    set_stepsize(0.001);
    set_simtime(0.0, 10.0);
    set_output("simulation_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
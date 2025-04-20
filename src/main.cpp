#include "sim.hpp"

int main()
{
    struct CircularModel {
        Integrator x, y;
        std::vector<Integrator*> integrators;
        AdamsBashforth4 solver;

        CircularModel(double x0, double y0) :
            x([&](double t, std::vector<double> y) { return -y[1]; }, x0),
            y([&](double t, std::vector<double> y) { return  y[0]; }, y0)
            {
                integrators = {&x, &y};
            }

        void step(double &t, double &h) {
            solver.step(t, h, integrators);
        }

        std::vector<double> output() {
            return {x.value, y.value};
        }
    };

    CircularModel model(1.0, 0.0);

    set_stepsize(0.1);
    set_simtime(0.0, 2 * M_PI);
    set_output("ab4_0.1_data.txt");
    start_simulation(model);

    return EXIT_SUCCESS;
}
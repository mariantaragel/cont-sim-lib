#include <cstdlib>
#include <vector>
#include <functional>
#include "sim.hpp"

int main()
{
    // Circular test
    // dx/dt = -y
    // dy/dt = x
    auto system = [](double t, std::vector<double> y) -> std::vector<double> {
        return {-y[1], y[0]};
    };

    set_simtime(0.0, 2 * 3.14);
    set_output("ab4.txt");
    AdamsBashforth4 ab4_solver(0.1);
    
    start_simulation(system, {1.0, 0.0}, ab4_solver);

    return EXIT_SUCCESS;
}
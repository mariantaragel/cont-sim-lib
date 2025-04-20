#include <vector>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include "euler.hpp"

class Euler {
public:
    Euler(double step) : h(step) {}

    std::vector<double> euler(std::function<std::vector<double> (double, std::vector<double>)> f, double t, std::vector<double> y)
    {
        std::vector<double> k = vec_scale(f(t, y), h);

        std::vector<double> y_n(y.size());
        for (size_t i = 0; i < y_n.size(); i++) {
            y_n[i] = y[i] + k[i];
        }

        return y_n;
    }

private:
    double h;

    static std::vector<double> vec_scale(const std::vector<double> &v, double k)
    {
        std::vector<double> result(v.size());
        for (size_t i = 0; i < v.size(); i++) {
            result[i] = k * v[i];
        }

        return result;
    }
};

int main()
{
    // Kruhový test:
    // dx/dt = -y
    // dy/dt = x
    auto system = [](double t, std::vector<double> y) -> std::vector<double> {
        return {-y[1], y[0]};
    };

    std::vector<double> y = {1.0, 0.0}; // Počiatočná podmienka
    double stepsize = 0.1;             // Veľkosť kroku
    double t = 0.0, t_max = 2 * M_PI;   // Počiatočný a koncový čas

    Euler solver(stepsize);

    std::ofstream file("simulation_data.txt");
    file << "# t\tx_num\ty_num\tx_exact\ty_exact\n";

    while (t <= t_max) {
        double x_exact = std::cos(t);
        double y_exact = std::sin(t);

        file << t << " " << y[0] << " " << y[1] << " " << x_exact << " " << y_exact << "\n";

        y = solver.euler(system, t, y); // Spočítaj nový stav
        t += stepsize;
    }

    file.close();
    std::cout << "Dáta uložené do simulation_data.txt\n";
    return EXIT_SUCCESS;
}
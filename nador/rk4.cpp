#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <fstream>

class RungeKutta4 {
public:
    RungeKutta4(double step) : h(step) {}

    std::vector<double> rk4(std::function<std::vector<double>(double, std::vector<double>)> f, double t, std::vector<double> &y)
    {
        std::vector<double> k1 = f(t, y);
        std::vector<double> k2 = f(t + h / 2, vec_sum(y, vec_scale(k1, h / 2)));
        std::vector<double> k3 = f(t + h / 2, vec_sum(y, vec_scale(k2, h / 2)));
        std::vector<double> k4 = f(t + h, vec_sum(y, vec_scale(k3, h)));

        std::vector<double> y_n(y.size());
        for (size_t i = 0; i < y_n.size(); i++) {
            y_n[i] = y[i] + (h / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
        }

        return y_n;
    }

private:
    double h;

    static std::vector<double> vec_sum(const std::vector<double> &v1, const std::vector<double> &v2)
    {
        std::vector<double> result(v1.size());
        for (size_t i = 0; i < v1.size(); i++) {
            result[i] = v1[i] + v2[i];
        }
        return result;
    }

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
    // Parametre modelu
    const double a1 = 0.1, a4 = 0.05, c1 = 0.02, c2 = 0.03, c3 = 0.02, c4 = 0.02;
    const double d1 = 0.02, d2 = 0.02, d3 = 0.02;
    const double k1 = 0.1, k2 = 0.05, k3 = 0.05, k4 = 0.02;
    const double tau = 0.5;
    const double rho = 1.0, alpha = 1.0, k = 0.5, gamma = 0.1;

    auto tumor_model = [=](double t, std::vector<double> y) -> std::vector<double> {
        double TI = y[0], TM = y[1], I = y[2], u = y[3];
        
        double TIdelay = (t >= tau) ? y[4] : TI;
        double TMdelay = (t >= tau) ? y[5] : TM;

        double dTI = 2 * a4 * TM - (c1 * I + d2) * TI - a1 * TIdelay;
        double dTM = a1 * TIdelay - d3 * TM - a4 * TM - c3 * TM * I - k1 * (1 - exp(-k2 * u)) * TM;
        double dI = k + (rho * I * pow(TI + TM, 2)) / (alpha + pow(TI + TM, 2)) - c2 * I * TI - c4 * TM * I - d1 * I - k3 * (1 - exp(-k4 * u)) * I;
        double du = -gamma * u;

        return {dTI, dTM, dI, du, TI, TM};
    };

    std::vector<double> y = {1.0, 1.0, 1.0, 0.5, 1.0, 1.0};
    double stepsize = 0.01, t = 0.0, t_max = 10.0;
    RungeKutta4 solver(stepsize);

    std::ofstream file("tumor_simulation_data.txt");
    file << "# t\tTI\tTM\tI\tu\n";

    while (t <= t_max) {
        file << t << " " << y[0] << " " << y[1] << " " << y[2] << " " << y[3] << "\n";
        y = solver.rk4(tumor_model, t, y);
        t += stepsize;
    }

    file.close();
    std::cout << "Dáta uložené do tumor_simulation_data.txt\n";
    return EXIT_SUCCESS;
}

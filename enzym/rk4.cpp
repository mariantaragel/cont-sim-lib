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
    // Enzymatická kinetika (s oneskorením):
    // s'(t) = -k * e(t) * s(t)
    // e'(t) = -k * e(t) * s(t) + k * e(t - tau) * s(t - tau)
    // p'(t) = k * e(t - tau) * s(t - tau)
    
    const double k = 1.0;    // Reakčná rýchlosť
    const double tau = 0.5;  // Oneskorenie

    auto enzyme_kinetics = [k, tau](double t, std::vector<double> y) -> std::vector<double> {
        double s = y[0];
        double e = y[1];
        double p = y[2];
        
        double s_tau = (t >= tau) ? y[3] : s; // Oneskorovaný substrát
        double e_tau = (t >= tau) ? y[4] : e; // Oneskorovaný enzým

        double ds = -k * e * s;
        double de = -k * e * s + k * e_tau * s_tau;
        double dp = k * e_tau * s_tau;

        return {ds, de, dp, s, e}; // Ukladáme aj oneskorované hodnoty
    };

    std::vector<double> y = {1.0, 1.0, 0.0, 1.0, 1.0}; // [substrát, enzým, produkt, oneskorený substrát, oneskorený enzým]
    double stepsize = 0.01;             // Veľkosť kroku
    double t = 0.0, t_max = 5.0;   // Počiatočný a koncový čas

    RungeKutta4 solver(stepsize);

    std::ofstream file("simulation_data.txt");
    file << "# t\ts_num\te_num\tp_num\n";

    while (t <= t_max) {
        file << t << " " << y[0] << " " << y[1] << " " << y[2] << "\n";

        y = solver.rk4(enzyme_kinetics, t, y); // Spočítaj nový stav
        t += stepsize;
    }

    file.close();
    std::cout << "Dáta uložené do simulation_data.txt\n";
    return EXIT_SUCCESS;
}
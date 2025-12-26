#include "Options/AsianOption.hpp"
#include "Models/GBM.hpp"
#include "Utils/GnuplotExporter.hpp"
#include <vector>
#include <iostream>

int main() {
    // 1. Configuration (Paramètres conformes à tes constructeurs)
    double S0 = 100.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;
    int steps = 100;
    int n_sims = 2000; 

    // GBM(S0, steps, mu, sigma)
    GBM gbm(S0, steps, r, sigma); 
    // AsianOption(T, r, K)
    AsianOption option(T, r, K);

    std::vector<double> stdPrices, minVarPrices;
    double sumStd = 0.0;
    double sumMinVar = 0.0;
    double df = option.getDiscountFactor(); // Utilise la méthode de ta classe Option

    std::cout << "Lancement de la simulation de convergence..." << std::endl;

    for (int i = 1; i <= n_sims; ++i) {
        // --- Standard MC ---
        Path pathStd = gbm.generatePath(T);
        sumStd += option.payoff(pathStd);
        stdPrices.push_back((sumStd / i) * df);

        // --- Min Var (Antithetic) MC ---
        // Utilise TA méthode generateMinVarPaths
        std::pair<Path, Path> pair = gbm.generateMinVarPaths(T);
        double meanPayoff = (option.payoff(pair.first) + option.payoff(pair.second)) / 2.0;
        sumMinVar += meanPayoff;
        minVarPrices.push_back((sumMinVar / i) * df);
    }

    // Sauvegarde via ton GnuplotExporter
    GnuplotExporter::saveConvergencePNG(stdPrices, minVarPrices, "convergence_asian.png");

    std::cout << "Simulation terminée. Graphique : output/convergence_asian.png" << std::endl;

    return 0;
}
#include "PricingEngine/EDPSolver.hpp"
#include <algorithm>
#include <cmath>

EDPSolver::EDPSolver(const Option& option_in, const GBM& model_in)
    : option(option_in), model(model_in) {}

double EDPSolver::solve(double S_max, int M, int N) const {
    double T = option.getT();
    double r = model.getMu();
    double sigma = model.getSigma();
    double K = S_max / 3.0; // Approximation si non fourni

    double dt = T / N;
    double dS = S_max / M;

    // Grille de prix à maturité (V_final)
    std::vector<double> V(M + 1);
    for (int i = 0; i <= M; ++i) {
        // Simulation d'un "Path" minimal pour utiliser ton payoff existant
        Path p({(double)i * dS}); 
        V[i] = option.payoff(p);
    }

    // Remontée dans le temps (Schéma explicite pour la démo, plus simple à coder)
    for (int j = N - 1; j >= 0; --j) {
        std::vector<double> V_next(M + 1);
        for (int i = 1; i < M; ++i) {
            double S = i * dS;
            double delta = (V[i+1] - V[i-1]) / (2 * dS);
            double gamma = (V[i+1] - 2*V[i] + V[i-1]) / (dS * dS);
            
            double theta = r * S * delta + 0.5 * sigma * sigma * S * S * gamma - r * V[i];
            V_next[i] = V[i] + dt * theta;
        }
        // Conditions aux limites (ex: Dirichlet pour Call)
        V_next[0] = 0; 
        V_next[M] = S_max - K * std::exp(-r * (T - j * dt));
        V = V_next;
    }

    // Interpolation pour trouver le prix à S0
    int idx = static_cast<int>(model.getS0() / dS);
    return V[idx];
}
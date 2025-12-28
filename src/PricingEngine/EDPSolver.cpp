#include "PricingEngine/EDPSolver.hpp"
#include <algorithm>
#include <cmath>

// LE CONSTRUCTEUR (Indispensable pour corriger l'erreur de "Undefined symbols")
EDPSolver::EDPSolver(const Option& option_in, const GBM& model_in)
    : option(option_in), model(model_in) {}

// LA METHODE DE CALCUL DE COURBE
std::pair<std::vector<double>, std::vector<double>> EDPSolver::calculateEDPCurve(double S_max, int M, int N) const {
    
    double T = option.getT(); // Assure-toi que c'est getExpiry() ou getT() selon ton Option.hpp
    double r = model.getMu();
    double sigma = model.getSigma();
    double dS = S_max / M;
    double dt = T / N;

    std::vector<double> V(M + 1);
    std::vector<double> S_vec(M + 1);

    // 1. Initialisation à maturité (t = T)
    for (int i = 0; i <= M; ++i) {
        S_vec[i] = i * dS;
        // Création d'un Path factice avec un seul point pour le payoff
        Path p({S_vec[i]}); 
        V[i] = option.payoff(p);
    }

    // 2. Boucle temporelle (Remontée de T vers 0)
    for (int j = N - 1; j >= 0; --j) {
        std::vector<double> V_next(M + 1);
        for (int i = 1; i < M; ++i) {
            double S = i * dS;
            
            // Discrétisation spatiale (Différences finies centrées)
            double delta = (V[i+1] - V[i-1]) / (2.0 * dS);
            double gamma = (V[i+1] - 2.0 * V[i] + V[i-1]) / (dS * dS);
            
            // Équation de Black-Scholes (Theta)
            double theta = r * S * delta + 0.5 * sigma * sigma * S * S * gamma - r * V[i];
            
            // Schéma explicite : V(t) = V(t+dt) + dt * Theta
            V_next[i] = V[i] + dt * theta;
        }

        // 3. Conditions aux limites
        V_next[0] = 0.0; // S = 0 => Option vaut 0
        // Pour S_max, on utilise la condition de linéarité (gamma = 0) ou la valeur intrinsèque
        V_next[M] = V[M]; 
        
        V = V_next;
    }

    return {S_vec, V};
}

// METHODE SOLVE (Pour obtenir le prix unique à S0)
double EDPSolver::solve(double S_max, int M, int N) const {
    auto curve = calculateEDPCurve(S_max, M, N);
    double dS = S_max / M;
    
    // Trouver l'index correspondant au prix S0 actuel
    int idx = static_cast<int>(std::round(model.getS0() / dS));
    if (idx < 0) idx = 0;
    if (idx > M) idx = M;
    
    return curve.second[idx];
}
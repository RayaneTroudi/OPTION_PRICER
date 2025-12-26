#include "Models/GBM.hpp"
#include "Models/RNG.hpp" // To access the Random Number Generator Singleton
#include <cmath>
#include <vector>
#include <algorithm>

GBM::GBM(double S0_in, int steps_in, double mu_in, double sigma_in)
    : AssetModel(S0_in, steps_in), mu(mu_in), sigma(sigma_in) 
{}

Path GBM::generatePath(double T) const {
    
    // 1. Calculate the time step size (dt = T / steps)
    double dt = T / steps; 

    // 2. Pre-calculate constant terms for computational efficiency
    
    // Deterministic term (drift): (mu - 0.5 * sigma^2) * dt
    double drift_term = (mu - 0.5 * sigma * sigma) * dt;
    
    // Volatility factor for the stochastic term: sigma * sqrt(dt)
    double vol_term_factor = sigma * std::sqrt(dt);

    // 3. Initialize path container
    std::vector<double> prices_data;
    prices_data.reserve(steps + 1);
    
    // Start with the initial price S0
    prices_data.push_back(S0); 

    double current_price = S0;

    // 4. Loop through time steps to generate the trajectory
    for (int i = 0; i < steps; ++i) {
        
        // Obtain a standard normal random variable Z ~ N(0, 1) via the RNG Singleton
        double Z = RNG::getInstance().getStandardNormal(); 
        
        // 5. Apply the discrete GBM update formula
        current_price *= std::exp(drift_term + vol_term_factor * Z);

        prices_data.push_back(current_price);
    }
    
    // 6. Return the constructed Path object
    return Path(prices_data);
}

std::pair<Path, Path> GBM::generateMinVarPaths(double T) const {
    
    // 1. Pré-calcul des constantes
    double dt = T / steps; 
    double drift_term = (mu - 0.5 * sigma * sigma) * dt;
    double vol_term_factor = sigma * std::sqrt(dt);

    // 2. Initialisation des deux trajectoires
    std::vector<double> prices_std;
    std::vector<double> prices_anti;
    prices_std.reserve(steps + 1);
    prices_anti.reserve(steps + 1);
    
    // Initialisation des prix (S0 est commun)
    prices_std.push_back(S0); 
    prices_anti.push_back(S0);
    
    double current_price_std = S0;
    double current_price_anti = S0;

    // 3. Boucle de simulation (N/2 itérations nécessaires si on génère les paires)
    for (int i = 0; i < steps; ++i) {
        
        // A. Générer un seul nombre normal Z
        double Z = RNG::getInstance().getStandardNormal(); 
        
        // B. Calculer les termes stochastiques pour Z et -Z
        double stoch_term_std = vol_term_factor * Z;    // Terme standard
        double stoch_term_anti = vol_term_factor * (-Z); // Terme antithétique
        
        // C. Mettre à jour le chemin standard (utilise Z)
        current_price_std *= std::exp(drift_term + stoch_term_std);
        prices_std.push_back(current_price_std);

        // D. Mettre à jour le chemin antithétique (utilise -Z)
        current_price_anti *= std::exp(drift_term + stoch_term_anti);
        prices_anti.push_back(current_price_anti);
    }
    
    // 4. Retourner la paire de chemins
    return std::make_pair(Path(prices_std), Path(prices_anti));
}



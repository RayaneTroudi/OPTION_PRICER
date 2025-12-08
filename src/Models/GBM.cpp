#include "Models/GBM.hpp"
#include "Models/RNG.hpp" // Pour accéder au générateur de nombres aléatoires
#include <cmath>
#include <vector>
#include <algorithm>

// --- Constructeur ---

// Le constructeur appelle simplement le constructeur de la classe de base AssetModel
// et initialise les paramètres spécifiques du GBM (drift et volatilité).
GBM::GBM(double S0_in, int steps_in, double mu_in, double sigma_in)
    : AssetModel(S0_in, steps_in), mu(mu_in), sigma(sigma_in) 
{}

// --- Implémentation de generatePath ---

Path GBM::generatePath(double T) const {
    
    // 1. Calcul du pas de temps (dt)
    double dt = T / steps; 

    // 2. Pré-calcul des termes constants pour l'efficacité
    // Terme de dérive (drift) : (mu - 0.5 * sigma^2) * dt
    double drift_term = (mu - 0.5 * sigma * sigma) * dt;
    
    // Facteur pour le terme stochastique : sigma * sqrt(dt)
    double vol_term_factor = sigma * std::sqrt(dt);

    // 3. Initialisation de la trajectoire
    std::vector<double> prices_data;
    prices_data.reserve(steps + 1);
    
    // Le prix initial S0
    prices_data.push_back(S0); 

    double current_price = S0;

    // 4. Boucle de simulation sur tous les pas de temps
    for (int i = 0; i < steps; ++i) {
        
        // Obtenir une variable normale standard Z ~ N(0, 1) via le Singleton RNG
        double Z = RNG::getInstance().getStandardNormal(); 
        
        // 5. Application de la formule de mise à jour discrète du GBM :
        // S(t+dt) = S(t) * exp[ (mu - 0.5*sigma^2)dt + sigma*sqrt(dt)*Z ]
        current_price *= std::exp(drift_term + vol_term_factor * Z);

        prices_data.push_back(current_price);
    }
    
    // 6. Retourner la trajectoire encapsulée dans l'objet Path
    return Path(prices_data);
}
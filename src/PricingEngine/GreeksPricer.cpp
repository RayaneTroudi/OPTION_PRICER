#include "PricingEngine/GreeksPricer.hpp"
#include "Models/GBM.hpp" // Nécessaire pour recréer le modèle GBM perturbé
#include "PricingEngine/PricingResult.hpp" // Pour accéder à PricingResult
#include <iostream>
#include <stdexcept>
#include <cmath>

GreeksPricer::GreeksPricer(const Option& option_in, const AssetModel& model_in)
    : option(option_in), model(model_in)
{}

double GreeksPricer::getPriceAtS(double S_new, int num_simulations) const {
    
    // La méthode 'dynamic_cast' est utilisée pour accéder aux paramètres spécifiques
    // d'un modèle concret (GBM) à partir de son interface (AssetModel).
    try {
        const GBM& gbm_model = dynamic_cast<const GBM&>(model);

        // 1. Crée un nouveau modèle GBM avec le prix initial S_new perturbé,
        // en conservant tous les autres paramètres (steps, mu, sigma).
        GBM new_gbm(S_new, gbm_model.getSteps(), gbm_model.getMu(), gbm_model.getSigma());
        
        // 2. Crée un pricer temporaire avec le nouveau modèle
        MonteCarloPricer temp_pricer(option, new_gbm);
        
        // 3. Calcule et retourne le prix
        return temp_pricer.calculatePrice(num_simulations).price;
        
    } catch (const std::bad_cast& e) {
        std::cerr << "Erreur: GreeksPricer (getPriceAtS) nécessite actuellement une instance de modèle GBM pour la perturbation de S0.\n";
        throw;
    }
}

double GreeksPricer::calculateDelta(int num_simulations, double epsilon) const {
    
    double S0_base = model.getS0();
    
    // Définir les prix perturbés
    double S_plus = S0_base + epsilon;
    double S_minus = S0_base - epsilon;
    
    // 1. Calculer V(S + epsilon)
    double V_plus = getPriceAtS(S_plus, num_simulations);
    
    // 2. Calculer V(S - epsilon)
    double V_minus = getPriceAtS(S_minus, num_simulations);
    
    // 3. Calculer Delta (Différence finie centrée)
    double delta = (V_plus - V_minus) / (2.0 * epsilon);
    
    return delta;
}

double GreeksPricer::calculateGamma(int num_simulations, double epsilon) const {
    
    double S0_base = model.getS0();
    
    // Définir les prix perturbés
    double S_plus = S0_base + epsilon;
    double S_minus = S0_base - epsilon;
    
    // 1. Calculer V(S + epsilon)
    double V_plus = getPriceAtS(S_plus, num_simulations);
    
    // 2. Calculer V(S - epsilon)
    double V_minus = getPriceAtS(S_minus, num_simulations);
    
    // 3. Calculer V(S) (le prix de base)
    double V_base = getPriceAtS(S0_base, num_simulations);
    
    // 4. Calculer Gamma (Différence finie de second ordre)
    // Gamma ≈ (V+ - 2*V_base + V-) / (epsilon^2)
    double gamma = (V_plus - 2.0 * V_base + V_minus) / (epsilon * epsilon);
    
    return gamma;
}
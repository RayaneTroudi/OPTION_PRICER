#include "PricingEngine/GreeksPricer.hpp"
#include "Models/GBM.hpp" // Nécessaire pour recréer le modèle GBM perturbé
#include "PricingEngine/PricingResult.hpp" // Pour accéder à PricingResult
#include <iostream>
#include <stdexcept>
#include <cmath>

// --- Constructeur ---

/**
 * @brief Constructs the Greeks Pricer by storing references to the Option and AssetModel interfaces.
 * @param option_in The option whose Greeks will be calculated.
 * @param model_in The asset model used for simulation.
 */
GreeksPricer::GreeksPricer(const Option& option_in, const AssetModel& model_in)
    : option(option_in), model(model_in)
{}

// --- Helper Function: Get Price at a Perturbed S0 ---

/**
 * @brief Helper function to compute the option price V for a given initial asset price S_new.
 * * It creates a temporary model and pricer instance to compute V(S_new).
 * @param S_new The perturbed initial asset price (S0 + or - epsilon).
 * @param num_simulations Number of paths for the pricing run.
 * @return The estimated price V at S_new.
 * @throws std::bad_cast If the model is not a GBM instance (as required for parameter cloning).
 */
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

// --- Calculate Delta Implementation (Finite Difference) ---

/**
 * @brief Estimates the Delta of the option using the central finite difference formula (FDM).
 * Formula: Delta ≈ (V(S + epsilon) - V(S - epsilon)) / (2 * epsilon)
 * @param num_simulations Number of paths for each pricing run.
 * @param epsilon The small perturbation in the initial price S0 (dS).
 * @return The estimated Delta value.
 */
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

// --- Calculate Gamma Implementation (Finite Difference) ---

/**
 * @brief Estimates the Gamma of the option using the central finite difference formula (FDM).
 * Formula: Gamma ≈ (V(S + epsilon) - 2*V(S) + V(S - epsilon)) / (epsilon^2)
 * @param num_simulations Number of paths for each pricing run.
 * @param epsilon The small perturbation in the initial price S0 (dS).
 * @return The estimated Gamma value.
 */
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
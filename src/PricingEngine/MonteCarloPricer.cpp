#include "PricingEngine/MonteCarloPricer.hpp"
#include <numeric>
#include <cmath>

// --- Constructeur ---

MonteCarloPricer::MonteCarloPricer(const Option& option_in, const AssetModel& model_in)
    : option(option_in), model(model_in)
{}

// --- Méthode de Pricing ---

PricingResult MonteCarloPricer::calculatePrice(int num_simulations) const {
    
    std::vector<double> realized_payoffs;
    realized_payoffs.reserve(num_simulations);
    
    double sum_payoffs = 0.0;
    
    // Le temps à l'échéance T est récupéré de l'objet Option
    double T = option.getT();

    // 1. Boucle de Simulation (le cœur de Monte Carlo)
    for (int i = 0; i < num_simulations; ++i) {
        
        // A. Générer la Trajectoire
        // Appel polymorphique : utilise le modèle concret (GBM)
        Path path = model.generatePath(T); 

        // B. Calculer le Payoff
        // Appel polymorphique : utilise la méthode payoff de l'option concrète (Call/Butterfly...)
        double payoff = option.payoff(path);
        
        realized_payoffs.push_back(payoff);
        sum_payoffs += payoff;
    }

    // 2. Actualisation et Moyenne (Estimation du Prix)

    // Facteur d'actualisation e^(-rT)
    double discount_factor = option.getDiscountFactor();
    
    // Prix non actualisé moyen (E[Payoff])
    double mean_payoff = sum_payoffs / num_simulations;
    
    // Prix de l'option (e^(-rT) * E[Payoff])
    double price = discount_factor * mean_payoff;
    
    // 3. Calcul de l'Erreur Standard (pour l'Intervalle de Confiance)
    
    // Calcul de la variance du payoff
    double sum_sq_diff = 0.0;
    for (double payoff : realized_payoffs) {
        double diff = payoff - mean_payoff;
        sum_sq_diff += diff * diff;
    }
    // Variance des payoffs (non actualisée)
    double payoff_variance = sum_sq_diff / (num_simulations - 1); 
    
    // Erreur standard de l'estimation du prix (Standard Error of the Mean, SEM)
    // SEM = [e^(-rT) * sqrt(Var(Payoff))] / sqrt(N)
    double standard_error = discount_factor * std::sqrt(payoff_variance / num_simulations);
    
    
    // 4. Retour du Résultat
    return PricingResult(price, standard_error, realized_payoffs);
}
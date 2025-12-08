#include <iostream>
#include <memory>
#include <cmath>

// --- BLOC CORE/OPTIONS ---
#include "include/Core/Path.hpp"
#include "include/Core/Option.hpp"
#include "include/Options/EuropeanCall.hpp" 

// --- BLOC MODELS ---
#include "include/Models/AssetModel.hpp"
#include "include/Models/GBM.hpp"
#include "include/Models/RNG.hpp" // Note: RNG doit être inclus pour son initialisation/utilisation

// --- BLOC PRICING ENGINE ---
#include "include/PricingEngine/MonteCarloPricer.hpp"
#include "include/PricingEngine/PricingResult.hpp"

int main() {
    
    // --- 1. PARAMÈTRES DE BASE ---
    
    // Paramètres financiers (selon la convention de Black-Scholes)
    const double S0 = 100.0;     // Prix initial du sous-jacent
    const double K = 105.0;      // Prix d'exercice (Strike)
    const double T = 1.0;        // Échéance (1 an)
    const double r = 0.05;       // Taux sans risque (Drift du GBM)
    const double sigma = 0.20;   // Volatilité
    
    // Paramètres de la simulation Monte Carlo
    const int STEPS = 100;           // Nombre de pas de temps par trajectoire
    const int NUM_SIMULATIONS = 500000; // Nombre de simulations pour la précision

    std::cout << "--- 📈 Démarrage du Pricer Monte Carlo ---\n";
    std::cout << "Option: European Call (K=" << K << ", T=" << T << ")\n";
    std::cout << "Modèle: GBM (r=" << r << ", sigma=" << sigma << ")\n";
    std::cout << "Simulations: " << NUM_SIMULATIONS << " / Pas: " << STEPS << "\n";
    std::cout << "------------------------------------------\n";

    // --- 2. CRÉATION DES OBJETS ---
    
    // Initialisation du RNG (facultatif si le Singleton est bien géré, mais assure que l'instance existe)
    RNG::getInstance(); 

    // Création de l'Option concrète (EuropeanCall)
    EuropeanCall call(T, r, K);
    
    // Création du Modèle concret (GBM)
    GBM gbm(S0, STEPS, r, sigma); // Utilisation de r comme drift (mu) pour le pricing risque-neutre

    // Création du Pricer (utilise les références aux interfaces Option et AssetModel)
    MonteCarloPricer pricer(call, gbm);
    
    // --- 3. EXÉCUTION DU PRICING ---
    
    std::cout << "Calcul en cours... ";
    
    // Lance la simulation et obtient les résultats
    PricingResult result = pricer.calculatePrice(NUM_SIMULATIONS);
    
    std::cout << "Terminé.\n";
    std::cout << "------------------------------------------\n";

    // --- 4. AFFICHAGE DES RÉSULTATS ---
    
    std::cout << "✅ RÉSULTATS DU PRICING MONTE CARLO :\n";
    std::cout << "Prix de l'option : " << result.price << "\n";
    std::cout << "Erreur standard (SEM) : " << result.standard_error << "\n";
    std::cout << "Intervalle de confiance à 95% :\n";
    std::cout << "  [" << result.confidenceInterval95Lower() << ", " 
              << result.confidenceInterval95Upper() << "]\n";
    
    // Pour une analyse plus poussée (et le futur graphique) :
    // std::cout << "Nombre de payoffs enregistrés : " << result.payoff_distribution.size() << "\n";
    
    return 0;
}
#include <iostream>
#include <memory>
#include <cmath>
#include <iomanip> // Pour le formatage de l'affichage

// --- BLOC CORE/OPTIONS ---
#include "Core/Path.hpp"
#include "Core/Option.hpp"
#include "Options/EuropeanButterFly.hpp" // <-- Changement : Inclusion de ButterflyOption
#include "Options/EuropeanCall.hpp" 

// --- BLOC MODELS ---
#include "Models/AssetModel.hpp"
#include "Models/GBM.hpp"
#include "Models/RNG.hpp" 

// --- BLOC PRICING ENGINE ---
#include "PricingEngine/MonteCarloPricer.hpp"
#include "PricingEngine/PricingResult.hpp"
#include "PricingEngine/GreeksPricer.hpp" 


int main() {
    
    // Pour un affichage clair des nombres à virgule flottante
    std::cout << std::fixed << std::setprecision(5);

    // --- 1. PARAMÈTRES FINANCIERS ---
    
    const double S0 = 100.0;     // Prix initial du sous-jacent
    const double T = 1.0;        // Échéance (1 an)
    const double r = 0.05;       // Taux sans risque (Drift)
    const double sigma = 0.20;   // Volatilité
    
    // Paramètres spécifiques du BUTTERFLY (K1 < K2 < K3)
    const double K1 = 95.0;      // Strike Inférieur
    const double K2 = 100.0;     // Strike Central (souvent At-the-Money)
    const double K3 = 105.0;     // Strike Supérieur

    // --- 2. PARAMÈTRES DE SIMULATION ---
    
    const int STEPS = 100;           
    const int NUM_SIMULATIONS = 10000; // Augmenté pour la stabilité des Greeks
    
    // Perturbation de S0 (0.1% de S0 est un bon point de départ pour le Gamma)
    const double EPSILON = 0.001 * S0; // Soit 0.1

    std::cout << "--- 📈 Démarrage du Pricer Monte Carlo ---\n";
    std::cout << "Option: Butterfly (K1=" << K1 << ", K2=" << K2 << ", K3=" << K3 << ") / Modèle: GBM\n";
    std::cout << "Simulations: " << NUM_SIMULATIONS << " / Epsilon: " << EPSILON << "\n";
    std::cout << "------------------------------------------\n";

    // --- 3. CRÉATION DES OBJETS ---
    
    RNG::getInstance(); 

    // Création de l'objet Butterfly Option
    ButterflyOption butterfly(T, r, K1, K2, K3); // <-- Changement ici !
    
    // Le Modèle GBM reste inchangé
    GBM gbm(S0, STEPS, r, sigma); 

    // --- 4. EXÉCUTION DU PRICING (PRIX V) ---
    
    MonteCarloPricer pricer(butterfly, gbm); // Utilise l'option Butterfly
    
    std::cout << "Calcul du Prix V... ";
    PricingResult result = pricer.calculatePrice(NUM_SIMULATIONS);
    std::cout << "Terminé.\n";
    
    // --- 5. EXÉCUTION DU CALCUL DES GREEKS ---
    
    // Le GreeksPricer peut utiliser n'importe quelle Option
    GreeksPricer greeks_pricer(butterfly, gbm); // Utilise l'option Butterfly
    
    std::cout << "Calcul des Greeks (FDM):\n";
    
    // Calcul du Delta
    std::cout << "  -> Calcul du Delta... ";
    double delta = greeks_pricer.calculateDelta(NUM_SIMULATIONS, EPSILON);
    std::cout << "Terminé.\n";
    
    // Calcul du Gamma
    // NOTE: Le Gamma de la Butterfly doit être NÉGATIF au centre (K2) !
    std::cout << "  -> Calcul du Gamma... ";
    double gamma = greeks_pricer.calculateGamma(NUM_SIMULATIONS, EPSILON);
    std::cout << "Terminé.\n";
    
    std::cout << "\n";

    // --- 6. AFFICHAGE ET VALIDATION ---
    
    std::cout << "✅ RÉSULTATS DU PRICING :\n";
    std::cout << "Prix de l'option (V) : " << result.price << "\n";
    std::cout << "Erreur standard (SEM) : " << result.standard_error << "\n";
    
    std::cout << "\n🎯 RÉSULTATS DES GREEKS :\n";
    std::cout << "Delta (∂V/∂S) : " << delta << "\n";
    std::cout << "Gamma (∂²V/∂S²) : " << gamma << "\n";
    std::cout << "------------------------------------------\n";
    
    // VALIDATION CLÉ POUR LA BUTTERFLY :
    // Le Prix (V) doit être positif.
    // Le Gamma (∂²V/∂S²) doit être NÉGATIF lorsque S0 = K2 (100) car la Butterfly est vendue à l'extérieur (Call(K2)).
    
    return 0;
}
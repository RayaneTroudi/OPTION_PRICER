#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

// --- CORE/OPTIONS ---
#include "Core/Path.hpp"
#include "Core/Option.hpp"
#include "Core/AnalyticPriced.hpp" // <-- Nouveau
#include "Options/EuropeanCall.hpp" 

// --- MODELS ---
#include "Models/AssetModel.hpp"
#include "Models/GBM.hpp"
#include "Models/RNG.hpp" 

// --- PRICING ENGINE ---
#include "PricingEngine/MonteCarloPricer.hpp"
#include "PricingEngine/PricingResult.hpp"
#include "PricingEngine/GreeksPricer.hpp" 

// NOTE: BlackScholesFormulas.hpp n'est plus nécessaire dans main.cpp car les méthodes 
// sont appelées via l'objet Call lui-même (meilleure encapsulation).

int main() {
    
    std::cout << std::fixed << std::setprecision(5);

    // --- 1. PARAMÈTRES FINANCIERS ---
    const double S0 = 100.0;     // Initial Price
    const double K = 105.0;      // Strike Price
    const double T = 1.0;        // Time to Maturity
    const double r = 0.05;       // Risk-free Rate
    const double sigma = 0.20;   // Volatility
    
    // --- 2. PARAMÈTRES DE SIMULATION ---
    const int STEPS = 100;           
    const int NUM_SIMULATIONS = 100000; 

    // Epsilon for Finite Difference Method (FDM)
    const double EPSILON = 0.001 * S0; 

    std::cout << "--- Monte Carlo Pricing Comparison (European Call) ---\n";
    std::cout << "S0: " << S0 << ", K: " << K << ", T: " << T << ", sigma: " << sigma << "\n";
    std::cout << "Total Simulations (N): " << NUM_SIMULATIONS << "\n";
    std::cout << "FDM Epsilon (d^S): " << EPSILON << "\n";
    std::cout << "------------------------------------------------------\n";

    // --- 3. OBJECT INSTANTIATION ---
    RNG::getInstance(); 
    
    // On travaille avec l'objet concret EuropeanCall
    EuropeanCall call_concrete(T, r, K); 
    
    // On peut utiliser la référence abstraite pour le pricer
    const Option& call = call_concrete; 

    GBM gbm(S0, STEPS, r, sigma); 
    MonteCarloPricer pricer(call, gbm);
    GreeksPricer greeks_pricer(call, gbm);

    // 4. PRICING (STANDARD & MIN VAR)
    
    std::cout << "-> Pricing STANDARD ...\n";
    PricingResult result_std = pricer.calculatePrice(NUM_SIMULATIONS);
    // ... (affichage standard) ...
    std::cout << "   Price V (Standard):      " << result_std.price << "\n";
    std::cout << "   Standard Error (SEM):    " << result_std.standard_error << "\n";
    
    std::cout << "\n-> Pricing REDUCTION VARIANCE ...\n";
    PricingResult result_minvar = pricer.calculatePriceMinVar(NUM_SIMULATIONS);
    double sem_reduction = (result_std.standard_error - result_minvar.standard_error) / result_std.standard_error * 100.0;
    std::cout << "   Price V (Min Var):       " << result_minvar.price << "\n";
    std::cout << "   Standard Error (SEM):    " << result_minvar.standard_error << "\n";
    std::cout << "   SEM Reduction achieved:  " << std::setprecision(2) << sem_reduction << "%" << std::setprecision(5) << "\n";

    std::cout << "======================================================\n";
    
    // 6. GREEKS CALCULATION (Analytic Formulas)

    std::cout << "-> GREEKS CALCULATION (ANALYTIC / Black-Scholes):\n";
    
    // TENTATIVE D'ACCÈS AUX MÉTHODES ANALYTIQUES VIA dynamic_cast
    const AnalyticPriced* analytic_option = dynamic_cast<const AnalyticPriced*>(&call);

    if (analytic_option) {
        // L'objet est bien une option 'vanille' supportant l'analyse BS.
        double delta_bs = analytic_option->getAnalyticDelta(S0, sigma);
        double gamma_bs = analytic_option->getAnalyticGamma(S0, sigma);
        double vega_bs = analytic_option->getAnalyticVega(S0, sigma);

        std::cout << "   Delta (Analytic) :       " << delta_bs << "\n";
        std::cout << "   Gamma (Analytic) :       " << gamma_bs << "\n";
        std::cout << "   Vega (Analytic) :        " << vega_bs << "\n";
    } else {
        std::cout << "   [Option non analytique. Impossible d'utiliser les formules BS.]\n";
    }
    
    std::cout << "------------------------------------------------------\n";
    
    // 7. GREEKS CALCULATION (FDM)
    
    std::cout << "-> GREEKS CALCULATION (NUMERIC / FDM):\n";
    
    double delta_fdm = greeks_pricer.calculateDelta(NUM_SIMULATIONS, EPSILON);
    double gamma_fdm = greeks_pricer.calculateGamma(NUM_SIMULATIONS, EPSILON);
    
    std::cout << "   Delta (FDM) :            " << delta_fdm << "\n";
    std::cout << "   Gamma (FDM) :            " << gamma_fdm << "\n";
    
    std::cout << "------------------------------------------------------\n";
    
    return 0;
}
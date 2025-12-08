#include "Options/EuropeanButterFly.hpp"
#include <algorithm> // For std::max

// --- Constructor ---

ButterflyOption::ButterflyOption(double T_in, double r_in, double K1_in, double K2_in, double K3_in)
    // Call the base class constructor (Option)
    : Option(T_in, r_in), K1(K1_in), K2(K2_in), K3(K3_in) 
{
    // A check could be added here to ensure K1 < K2 < K3 for a standard butterfly.
}

// --- Payoff Implementation ---

double ButterflyOption::payoff(const Path& path) const {
    // 1. Get the final price S_T
    double S_T = path.getFinalPrice(); 
    
    // 2. Calculate the Payoff components:
    
    // Leg 1: Buy Call K1
    double payoff1 = std::max(S_T - K1, 0.0);
    
    // Leg 2: Sell 2 Calls K2 (Payoff is subtracted twice)
    double payoff2 = 2.0 * std::max(S_T - K2, 0.0);
    
    // Leg 3: Buy Call K3
    double payoff3 = std::max(S_T - K3, 0.0);
    
    // 3. Combine the legs: Payoff = Call(K1) - 2 * Call(K2) + Call(K3)
    double final_payoff = payoff1 - payoff2 + payoff3;
    
    // 4. Return the combined payoff
    return final_payoff;
}
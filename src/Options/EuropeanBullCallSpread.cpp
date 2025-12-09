#include "Options/EuropeanBullCallSpread.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>


CallSpread::CallSpread(double T_in, double r_in, double K1_in, double K2_in)
    // Initialize base class (EuropeanOption) and strikes K1, K2.
    : EuropeanOption(T_in, r_in, K1_in), K1(K1_in), K2(K2_in) 
{
    // Constraint check: Bought strike K1 must be lower than sold strike K2.
    if (K1 >= K2) {
        throw std::invalid_argument("Error: For a Call Spread, the bought strike K1 must be strictly lower than the sold strike K2 (K1 < K2).");
    }
}


double CallSpread::payoff(const Path& path) const {
    
    double S_T = path.getFinalPrice();
    
    // 1. Payoff of the Bought Call (Strike K1)
    double payoff_bought = std::max(S_T - K1, 0.0);
    
    // 2. Payoff of the Sold Call (Strike K2)
    double payoff_sold = std::max(S_T - K2, 0.0);

    // 3. Total Payoff: Long Call (K1) - Short Call (K2)
    // The result is bounded between 0 and (K2 - K1).
    return payoff_bought - payoff_sold;
}
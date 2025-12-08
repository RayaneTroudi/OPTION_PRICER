#include "Options/EuropeanPut.hpp"
#include <algorithm> // For std::max
#include <stdexcept> // Optional: for error handling if path is empty

// --- Constructor ---

EuropeanPut::EuropeanPut(double T, double r, double K)
    // Call the base class constructor (EuropeanOption)
    // which handles the initialization of T, r, and K.
    : EuropeanOption(T, r, K) 
{
    // No other specific initialization is necessary for this simple option.
}

// --- Payoff Implementation ---

double EuropeanPut::payoff(const Path& path) const {
    // 1. Get the final price S_T (only required for European options)
    double S_T = path.getFinalPrice(); 
    
    // 2. Calculate the Payoff: max(K - S_T, 0)
    // K (Strike) is accessible here because it is 'protected' in EuropeanOption.
    
    return std::max(K - S_T, 0.0);
}
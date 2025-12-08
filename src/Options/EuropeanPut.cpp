#include "Options/EuropeanPut.hpp"
#include <algorithm> // Required for std::max
#include <stdexcept> // Optional: for error handling if path is empty

// --- Constructor Implementation ---

/**
 * @brief Constructor for the European Put option.
 * * Calls the constructor of the base class EuropeanOption, 
 * which initializes T, r, and K.
 * @param T Time to maturity.
 * @param r Risk-free rate.
 * @param K Strike Price.
 */
EuropeanPut::EuropeanPut(double T, double r, double K)
    // Call the base class constructor (EuropeanOption)
    : EuropeanOption(T, r, K) 
{
    // No other specific initialization is necessary for this simple option.
}

// --- Payoff Implementation ---

/**
 * @brief Calculates the option's payoff at maturity.
 * * The payoff for a European Put is defined as: max(K - S_T, 0).
 * @param path The simulated price path (only the final price S_T is relevant).
 * @return The raw (undiscounted) payoff value.
 */
double EuropeanPut::payoff(const Path& path) const {
    // 1. Get the final price S_T (only required for European options)
    double S_T = path.getFinalPrice(); 
    
    // 2. Calculate the Payoff: max(K - S_T, 0)
    // K (Strike) is accessible because it is 'protected' in EuropeanOption.
    
    return std::max(K - S_T, 0.0);
}
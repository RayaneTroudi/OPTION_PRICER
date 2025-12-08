#include "Options/EuropeanCall.hpp"
#include <algorithm> // Required for std::max

// --- Constructor Implementation ---

/**
 * @brief Constructor for the European Call option.
 * * Calls the constructor of the base class EuropeanOption, 
 * which initializes T, r, and K.
 * @param T_in Time to maturity.
 * @param r_in Risk-free rate.
 * @param K_in Strike Price.
 */
EuropeanCall::EuropeanCall(double T_in, double r_in, double K_in)
    : EuropeanOption(T_in, r_in, K_in) {}


// --- Payoff Implementation ---

/**
 * @brief Calculates the option's payoff at maturity.
 * * The payoff for a European Call is defined as: max(S_T - K, 0).
 * @param path The simulated price path (only the final price S_T is relevant).
 * @return The raw (undiscounted) payoff value.
 */
double EuropeanCall::payoff(const Path& path) const {
    // 1. Get the final price S_T from the path
    double S_T = path.getFinalPrice();
    
    // 2. Return the maximum of (S_T - K) and zero
    // K (Strike) is accessible because it is 'protected' in the base class EuropeanOption.
    return std::max(S_T - K, 0.0);
};
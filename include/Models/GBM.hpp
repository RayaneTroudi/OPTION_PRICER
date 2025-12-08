#ifndef GBM_HPP
#define GBM_HPP

#include "AssetModel.hpp" // Inherits from AssetModel
#include "RNG.hpp"        // Assumed Random Number Generator utility

/**
 * @brief Represents the Geometric Brownian Motion model for asset price simulation.
 * * It is a concrete implementation of AssetModel.
 * The price S(t) follows dS/S = mu*dt + sigma*dW.
 */
class GBM : public AssetModel {
public:
    // --- Constructor ---
    
    /**
     * @brief Constructs the GBM model.
     * @param S0_in Initial asset price.
     * @param steps_in Number of time steps.
     * @param mu_in Drift (risk-neutral rate r or actual return).
     * @param sigma_in Volatility.
     */
    GBM(double S0_in, int steps_in, double mu_in, double sigma_in);

    // --- Essential Method Implementation ---
    
    /**
     * @brief Generates a single Path of prices using the GBM formula.
     * @param T The time to maturity.
     * @return The simulated Path object.
     */
    Path generatePath(double T) const override;

private:
    double mu;      // Drift parameter (often the risk-free rate 'r' in pricing)
    double sigma;   // Volatility parameter

    // A static RNG is often used to ensure all GBM instances share the same generation setup.
    // We'll assume a global access or pass it during construction for thread safety later.
    // For simplicity now, let's assume we create/access an RNG object within the implementation.
};

#endif // GBM_HPP
#include "Models/GBM.hpp"
#include "Models/RNG.hpp" // To access the Random Number Generator Singleton
#include <cmath>
#include <vector>
#include <algorithm>

// --- Constructor ---

/**
 * @brief Constructor for the Geometric Brownian Motion (GBM) model.
 * * Calls the base class AssetModel constructor and initializes the specific
 * parameters of the GBM process (mu and sigma).
 * @param S0_in Initial asset price.
 * @param steps_in Number of time steps.
 * @param mu_in Drift parameter (often the risk-free rate 'r').
 * @param sigma_in Volatility parameter.
 */
GBM::GBM(double S0_in, int steps_in, double mu_in, double sigma_in)
    : AssetModel(S0_in, steps_in), mu(mu_in), sigma(sigma_in) 
{}

// --- Path Generation Implementation ---

/**
 * @brief Generates a single Path of prices using the discrete-time GBM formula.
 * The price update follows: S(t+dt) = S(t) * exp[ (mu - 0.5*sigma^2)dt + sigma*sqrt(dt)*Z ]
 * @param T The time to maturity.
 * @return The simulated Path object.
 */
Path GBM::generatePath(double T) const {
    
    // 1. Calculate the time step size (dt = T / steps)
    double dt = T / steps; 

    // 2. Pre-calculate constant terms for computational efficiency
    
    // Deterministic term (drift): (mu - 0.5 * sigma^2) * dt
    double drift_term = (mu - 0.5 * sigma * sigma) * dt;
    
    // Volatility factor for the stochastic term: sigma * sqrt(dt)
    double vol_term_factor = sigma * std::sqrt(dt);

    // 3. Initialize path container
    std::vector<double> prices_data;
    prices_data.reserve(steps + 1);
    
    // Start with the initial price S0
    prices_data.push_back(S0); 

    double current_price = S0;

    // 4. Loop through time steps to generate the trajectory
    for (int i = 0; i < steps; ++i) {
        
        // Obtain a standard normal random variable Z ~ N(0, 1) via the RNG Singleton
        double Z = RNG::getInstance().getStandardNormal(); 
        
        // 5. Apply the discrete GBM update formula
        current_price *= std::exp(drift_term + vol_term_factor * Z);

        prices_data.push_back(current_price);
    }
    
    // 6. Return the constructed Path object
    return Path(prices_data);
}
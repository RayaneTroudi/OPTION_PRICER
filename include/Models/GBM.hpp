#ifndef GBM_HPP
#define GBM_HPP

#include "AssetModel.hpp" 
#include "RNG.hpp"        


/**
 * @brief Represents the Geometric Brownian Motion model for asset price simulation.
 * * It is a concrete implementation of AssetModel.
 * The price S(t) follows dS/S = mu*dt + sigma*dW.
 */
class GBM : public AssetModel {

    public:

        /**
         * @brief Constructs the GBM model.
         * @param S0_in Initial asset price. 
         * @param steps_in Number of time steps.
         * @param mu_in Drift (risk-neutral rate r or actual return).
         * @param sigma_in Volatility.
         */
        GBM(double S0_in, int steps_in, double mu_in, double sigma_in);
        
        /**
         * @brief Generates a single Path of prices using the GBM formula.
         * @param T The time to maturity.
         * @return The simulated Path object.
         */
        Path generatePath(double T) const override;

        /**
         * @brief Generates a pair of antithetic paths (Path and Path') for variance reduction.
         * * The pair is based on the same random sequence Z and its opposite -Z.
         * @param T The time to maturity.
         * @return A std::pair<Path, Path> containing the standard path and the antithetic path.
         */
        std::pair<Path, Path> generateMinVarPaths(double T) const; 
        
        /**
         * @brief Getter for the drift parameter (mu).
         */
        double getMu() const { return mu; }

        /**
         * @brief Getter for the volatility parameter (sigma).
         */
        double getSigma() const { return sigma; }
        
    private:

        double mu;      // Drift parameter (often the risk-free rate 'r' in pricing)
        double sigma;   // Volatility parameter


};

#endif 
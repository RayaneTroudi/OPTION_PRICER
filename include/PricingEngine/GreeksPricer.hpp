#ifndef GREEKSPRICE_HPP
#define GREEKSPRICE_HPP

#include "../Core/Option.hpp"
#include "../Models/AssetModel.hpp"
#include "MonteCarloPricer.hpp"

/**
 * @brief Utility class to calculate option Greeks (Delta, Gamma, Vega, etc.) 
 * using the Finite Difference Method (FDM) applied to Monte Carlo pricing.
 * * It relies on running the MonteCarloPricer multiple times with perturbed input parameters.
 */
class GreeksPricer {

    public:

        /**
         * @brief Constructor for the Greeks Pricer.
         * @param option_in The option whose Greeks are to be calculated.
         * @param model_in The asset model to use for simulation.
         */
        GreeksPricer(const Option& option_in, const AssetModel& model_in);

        /**
         * @brief Estimates the Delta of the option using the central finite difference formula.
         * Formula: Delta ≈ (V(S + epsilon) - V(S - epsilon)) / (2 * epsilon)
         * @param num_simulations Number of paths for each pricing run (V+, V-).
         * @param epsilon The small perturbation in the initial price S0 (dS).
         * @return The estimated Delta value.
         */
        double calculateDelta(int num_simulations, double epsilon) const;

        /**
         * @brief Estimates the Gamma of the option using the central finite difference formula.
         * Formula: Gamma ≈ (V(S + epsilon) - 2*V(S) + V(S - epsilon)) / (epsilon^2)
         * @param num_simulations Number of paths for each pricing run.
         * @param epsilon The small perturbation in the initial price S0 (dS).
         * @return The estimated Gamma value.
         */
        double calculateGamma(int num_simulations, double epsilon) const;
        
    private:

        const Option& option;
        const AssetModel& model;

        /**
         * @brief Helper function to compute the price V for a given initial asset price S_new.
         * * This helper handles the creation of the perturbed AssetModel instance.
         * @param S_new The perturbed initial asset price.
         * @param num_simulations Number of paths for the pricing run.
         * @return The estimated price V at S_new.
         */
        double getPriceAtS(double S_new, int num_simulations) const;

    };

#endif 
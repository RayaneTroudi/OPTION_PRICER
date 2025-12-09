#ifndef MONTECARLOPRICER_HPP
#define MONTECARLOPRICER_HPP

// Inclusion of abstract interfaces and the result structure
#include "../Core/Option.hpp"
#include "../Models/AssetModel.hpp"
#include "PricingResult.hpp"

/**
 * @brief The pricing engine using the Monte Carlo method.
 * It is responsible for executing simulations and calculating the discounted price.
 */
class MonteCarloPricer {

    public:

        /**
         * @brief Constructs the pricer by taking references to abstract interfaces.
         * @param option_in The option to be priced (Option abstract interface).
         * @param model_in The simulation model to use (AssetModel abstract interface).
         */
        MonteCarloPricer(const Option& option_in, const AssetModel& model_in);

        /**
         * @brief Launches the standard Monte Carlo simulation.
         * @param num_simulations Number of paths to generate.
         * @return A PricingResult object containing the price, standard error, and distribution.
         */
        PricingResult calculatePrice(int num_simulations) const;

        /**
         * @brief Executes the Monte Carlo simulation using the Antithetic Variates method (Min Var).
         * * The number of path pairs generated is num_simulations / 2.
         * @param num_simulations The TOTAL number of paths (standard + antithetic). Must be even.
         * @return A PricingResult object.
         */
        PricingResult calculatePriceMinVar(int num_simulations) const; // <-- New method

    private:

        const Option& option;
        const AssetModel& model;
};

#endif
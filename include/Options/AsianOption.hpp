#ifndef ASIANOPTION_HPP
#define ASIANOPTION_HPP

#include "EuropeanOption.hpp"
#include <vector>

/**
 * @brief Represents an Asian Call Option with an arithmetic average price payoff.
 * This is a path-dependent option.
 */
class AsianOption : public EuropeanOption {
    
    public:
        /**
         * @brief Constructor for the Asian Option.
         * @param T_in Time to maturity.
         * @param r_in Risk-free rate.
         * @param K_in Strike price.
         */
        AsianOption(double T_in, double r_in, double K_in);

        /**
         * @brief Calculates the option's payoff at maturity.
         * Payoff is based on the arithmetic average price of the underlying asset over the path.
         * Payoff = max(S_Average - K, 0)
         * @param path The simulated price path (used to calculate the average price).
         * @return The raw (undiscounted) payoff value.
         */
        double payoff(const Path& path) const override;

    };

#endif 
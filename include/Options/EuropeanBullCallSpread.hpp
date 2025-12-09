#ifndef CALLSPREAD_HPP
#define CALLSPREAD_HPP

#include "../Core/Option.hpp"
#include "EuropeanOption.hpp"
#include <algorithm> // Required for max in payoff calculation

/**
 * @brief Represents a Bull Call Spread option strategy.
 * * This involves buying a Call with strike K1 and selling a Call with strike K2 (K1 < K2).
 */
class CallSpread : public EuropeanOption {
public:
    /**
     * @brief Constructor for the Call Spread.
     * @param T_in Time to maturity.
     * @param r_in Risk-free rate.
     * @param K1_in Strike of the bought Call (lower strike).
     * @param K2_in Strike of the sold Call (higher strike).
     */
    CallSpread(double T_in, double r_in, double K1_in, double K2_in);

    /**
     * @brief Calculates the option's payoff at maturity.
     * Payoff = max(S_T - K1, 0) - max(S_T - K2, 0)
     * @param path The simulated price path (only the final price S_T is relevant).
     * @return The raw (undiscounted) payoff value.
     */
    double payoff(const Path& path) const override;

private:
    double K1; // Strike of the bought Call (K_low)
    double K2; // Strike of the sold Call (K_high)
};

#endif // CALLSPREAD_HPP
#ifndef EUROPEANCALL_HPP
#define EUROPEANCALL_HPP    

#include "EuropeanOption.hpp" 
#include "../Core/Path.hpp"   

/**
 * @brief Represents a European Call Option (Option d'Achat Européenne).
 * * This is a concrete class that implements the specific payoff function 
 * for a basic vanilla call option: max(S_T - K, 0).
 */
class EuropeanCall : public EuropeanOption {

    public:

        /**
         * @brief Constructor for the European Call option.
         * @param T_in Time to maturity.
         * @param r_in Risk-free rate.
         * @param K_in Strike Price.
         */
        EuropeanCall(double T_in, double r_in, double K_in);

        /**
         * @brief Concrete implementation of the option's payoff calculation.
         * Payoff formula: max(S_T - K, 0).
         * @param path The simulated price path (only the final price S_T is relevant).
         * @return The raw (undiscounted) payoff value at maturity.
         */
        double payoff(const Path& path) const override;
};


#endif // EUROPEANCALL_HPP
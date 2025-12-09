#ifndef EUROPEANCALL_HPP
#define EUROPEANCALL_HPP    

#include "EuropeanOption.hpp" 
#include "../Core/Path.hpp" 
#include "Core/AnalyticPriced.hpp"  

/**
 * @brief Represents a European Call Option (Option d'Achat Européenne).
 * * This is a concrete class that implements the specific payoff function 
 * for a basic vanilla call option: max(S_T - K, 0).
 */
class EuropeanCall : public EuropeanOption, public AnalyticPriced {

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

        /** 
         * @brief Calculates the analytical Delta using the Black-Scholes formula.
         * @param S Current asset price.
         * @param sigma Volatility of the underlying asset.
         * @return The analytical Delta value.
         */
        double getAnalyticDelta(double S, double sigma) const override; 

        /**
         * @brief Get the Analytic Gamma object
         * 
         * @param S 
         * @param sigma 
         * @return double 
         */
        double getAnalyticGamma(double S, double sigma) const override;

        /**
         * @brief Get the Analytic Vega object
         * 
         * @param S 
         * @param sigma 
         * @return double 
         */
        double getAnalyticVega(double S, double sigma) const override;
};


#endif // EUROPEANCALL_HPP
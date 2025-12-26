#ifndef BUTTERFLYOPTION_HPP
#define BUTTERFLYOPTION_HPP

#include "../Core/Option.hpp" 
#include "../Core/Path.hpp"    
#include <vector>

/**
 * @brief Represents a Long Call Butterfly Option.
 * * This option is constructed from three calls with three different strikes (K1 < K2 < K3).
 * * Payoff is: max(S_T - K1, 0) - 2 * max(S_T - K2, 0) + max(S_T - K3, 0).
 */
class EuropeanButterFly : public Option {

    public:

        /**
         * @brief Constructor. Initializes T, r, and the three strikes.
         * @param T_in Time to maturity.
         * @param r_in Risk-free rate.
         * @param K1_in Lower Strike (K1).
         * @param K2_in Middle Strike (K2), usually K2 = (K1 + K3) / 2.
         * @param K3_in Upper Strike (K3).
         */
        EuropeanButterFly(double T_in, double r_in, double K1_in, double K2_in, double K3_in);
        
        /**
         * @brief Concrete implementation of the payoff calculation for the Call Butterfly.
         * @param path The simulated price path 
         * @return The raw gain at maturity.
         */
        double payoff(const Path& path) const override;

    private:

        double K1;
        double K2;
        double K3;

};

#endif 
#ifndef EUROPEANPUT_HPP
#define EUROPEANPUT_HPP

#include "EuropeanOption.hpp" 
#include "../Core/Path.hpp"    // Nécessaire pour le type Path

/**
 * @brief Represents a European Put option (Option de Vente Européenne).
 * * This is a concrete class implementing the specific payoff logic.
 */
class EuropeanPut : public EuropeanOption {

    public:
        
        /**
         * @brief Constructor. Initializes T, r, and K via the base class.
         * @param T Time to maturity.
         * @param r Risk-free rate.
         * @param K Strike Price.
         */
        EuropeanPut(double T, double r, double K);

        /**
         * @brief Concrete implementation of the payoff calculation: max(K - S_T, 0).
         * @param path The simulated price path (only the final price S_T is used).
         * @return The raw (undiscounted) gain at maturity.
         */
        double payoff(const Path& path) const override;
    };

#endif 
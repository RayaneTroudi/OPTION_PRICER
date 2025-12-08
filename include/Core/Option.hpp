#ifndef OPTION_HPP
#define OPTION_HPP

#include <cmath>
#include <vector>  
#include <iostream> 

#include "Core/Path.hpp"

/**
 * @brief Abstract base class for all derivative options (vanilla and exotic).
 * * This class defines the common parameters (T, r) and the core interface 
 * for payoff calculation. It cannot be instantiated directly.
 */
class Option{

protected: 

    /**
     * @brief Time to maturity (in years).
     */
    double T;
    
    /**
     * @brief Risk-free interest rate (annualized).
     */
    double r;

public:
    
    // --- Constructor & Destructor ---
    
    /**
     * @brief Constructor for the base option.
     * @param T_in Time to maturity.
     * @param r_in Risk-free rate.
     */
    Option(double T_in, double r_in) : T(T_in), r(r_in) {}

    /**
     * @brief Virtual destructor. Essential for polymorphism and proper memory cleanup 
     * when deleting derived option objects via a base class pointer.
     */
    virtual ~Option() = default;

    // --- Core Interface Method ---

    /**
     * @brief Pure virtual method to calculate the option's payoff at maturity.
     * Must be implemented by all concrete derived classes (e.g., EuropeanCall, AsianCall).
     * @param path The simulated price path.
     * @return The raw (undiscounted) payoff value.
     */
    virtual double payoff(const Path& path) const = 0;

    // --- Utility Methods ---

    /**
     * @brief Getter for the time to maturity.
     * @return T.
     */
    double getT() const { return T; }
    
    /**
     * @brief Getter for the risk-free rate.
     * @return r.
     */
    double getR() const { return r; }

    /**
     * @brief Calculates the continuous compounding discount factor.
     * Formula: exp(-r * T)
     * @return The discount factor.
     */
    double getDiscountFactor() const {
        return std::exp(-r * T);
    }

};

#endif // OPTION_HPP
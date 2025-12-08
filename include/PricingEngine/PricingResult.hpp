#ifndef PRICINGRESULT_HPP
#define PRICINGRESULT_HPP

#include <vector>
#include <cmath> // For std::sqrt, std::abs in future methods

/**
 * @brief Structure/Classe pour stocker et rapporter les résultats de la simulation Monte Carlo.
 * Elle contient le prix estimé, l'erreur statistique, et la distribution des payoffs.
 */
class PricingResult {
public:
    double price;
    double standard_error;
    
    // The distribution of realized payoffs is stored for variance calculation and graphing.
    std::vector<double> payoff_distribution;

    /**
     * @brief Constructor for initializing the results.
     * @param p The estimated option price.
     * @param se The standard error of the estimation.
     * @param dist The vector of all realized payoffs.
     */
    PricingResult(double p, double se, const std::vector<double>& dist)
        : price(p), standard_error(se), payoff_distribution(dist) {}
    
    // --- Reporting Methods ---
    
    /**
     * @brief Calculates the width of the 95% confidence interval.
     * The confidence interval is typically Price +/- 1.96 * Standard Error.
     * @return 1.96 * standard_error.
     */
    double confidenceInterval95Width() const { 
        // 1.96 is the approximate Z-score for 95% confidence
        return 1.96 * standard_error; 
    }
    
    /**
     * @brief Returns the lower bound of the 95% confidence interval.
     */
    double confidenceInterval95Lower() const {
        return price - confidenceInterval95Width();
    }
    
    /**
     * @brief Returns the upper bound of the 95% confidence interval.
     */
    double confidenceInterval95Upper() const {
        return price + confidenceInterval95Width();
    }
};

#endif // PRICINGRESULT_HPP
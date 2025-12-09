#ifndef BLACKSCHOLESFORMULAS_HPP
#define BLACKSCHOLESFORMULAS_HPP

#include <cmath>

/**
 * @brief Namespace containing analytical formulas for the Black-Scholes model.
 * These functions are used for pricing European vanilla options and calculating 
 * their Greeks (sensitivities).
 */
namespace BlackScholesFormulas {

    /**
     * @brief Standard Normal Probability Density Function (PDF: phi(x)).
     * @param x The z-value for which to calculate the density.
     * @return The density value (height of the bell curve).
     */
    double N_pdf(double x);

    /**
     * @brief Standard Normal Cumulative Distribution Function (CDF: Phi(x)).
     * @param x The z-value for which to calculate the cumulative probability.
     * @return The cumulative probability of the standard normal distribution.
     */
    double N_cdf(double x);


    /**
     * @brief Calculates the Black-Scholes d1 and d2 parameters.
     * These parameters are essential for all pricing and Greeks formulas.
     * @param S Current price of the underlying asset.
     * @param K Strike price of the option.
     * @param T Time remaining until maturity (in years).
     * @param r Risk-free rate.
     * @param sigma Volatility of the asset.
     * @param d1 Reference to store the d1 result.
     * @param d2 Reference to store the d2 result.
     */
    void calculate_d1_d2(double S, double K, double T, double r, double sigma, 
                         double& d1, double& d2);

    // --- Analytic Greeks for European Options (BS Model) ---

    /**
     * @brief Calculates the analytical Delta (sensitivity to asset price S) for a European Call.
     * Delta = Phi(d1).
     * @param S Current price of the underlying asset.
     * @param K Strike price of the option.
     * @param T Time remaining until maturity (in years).
     * @param r Risk-free rate.
     * @param sigma Volatility of the asset.
     * @return The Delta value.
     */
    double deltaCall(double S, double K, double T, double r, double sigma);

    /**
     * @brief Calculates the analytical Gamma (sensitivity of Delta) for a European Call or Put.
     * Gamma is the same for both Call and Put.
     * @param S Current price of the underlying asset.
     * @param K Strike price of the option.
     * @param T Time remaining until maturity (in years).
     * @param r Risk-free rate.
     * @param sigma Volatility of the asset.
     * @return The Gamma value.
     */
    double gammaCallPut(double S, double K, double T, double r, double sigma);

    /**
     * @brief Calculates the analytical Vega (sensitivity to volatility) for a European Call or Put.
     * Vega is the same for both Call and Put.
     * @param S Current price of the underlying asset.
     * @param K Strike price of the option.
     * @param T Time remaining until maturity (in years).
     * @param r Risk-free rate.
     * @param sigma Volatility of the asset.
     * @return The Vega value.
     */
    double vegaCallPut(double S, double K, double T, double r, double sigma);
}

#endif
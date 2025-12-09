#ifndef BLACKSCHOLESFORMULAS_HPP
#define BLACKSCHOLESFORMULAS_HPP

#include <cmath>

namespace BlackScholesFormulas {

    /**
     * @brief Standard Normal Probability Density Function (PDF: phi(x)).
     */
    double N_pdf(double x);

    /**
     * @brief Standard Normal Cumulative Distribution Function (CDF: Phi(x)).
     */
    double N_cdf(double x);

    /**
     * @brief Helper function to calculate d1 and d2 parameters used in Black-Scholes formulas.
     * @param S Current asset price.
     * @param K Strike price.
     * @param T Time to maturity.
     * @param r Risk-free interest rate.
     * @param sigma Volatility of the underlying asset.
     * @param d1 Reference to store the calculated d1 value.
     * @param d2 Reference to store the calculated d2 value.
     */
    void calculate_d1_d2(double S, double K, double T, double r, double sigma, 
                         double& d1, double& d2);

    double deltaCall(double S, double K, double T, double r, double sigma);

    double gammaCallPut(double S, double K, double T, double r, double sigma);

    double vegaCallPut(double S, double K, double T, double r, double sigma);
}

#endif 
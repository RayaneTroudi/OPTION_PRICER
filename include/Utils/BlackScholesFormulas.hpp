#ifndef BLACKSCHOLESFORMULAS_HPP
#define BLACKSCHOLESFORMULAS_HPP

#include <cmath>

namespace BlackScholesFormulas {

    // --- Core Mathematical Functions ---

    /**
     * @brief Standard Normal Probability Density Function (PDF: phi(x)).
     */
    double N_pdf(double x);

    /**
     * @brief Standard Normal Cumulative Distribution Function (CDF: Phi(x)).
     */
    double N_cdf(double x);

    // --- Helper Functions (d1 and d2) ---
    
    void calculate_d1_d2(double S, double K, double T, double r, double sigma, 
                         double& d1, double& d2);

    // --- Analytic Greeks for European Options (BS Model) ---

    double deltaCall(double S, double K, double T, double r, double sigma);

    double gammaCallPut(double S, double K, double T, double r, double sigma);

    double vegaCallPut(double S, double K, double T, double r, double sigma);
}

#endif // BLACKSCHOLESFORMULAS_HPP
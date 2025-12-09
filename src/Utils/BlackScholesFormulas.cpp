#include "Utils/BlackScholesFormulas.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

// Define M_PI if it's not defined by the cmath implementation
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace BlackScholesFormulas {

    // --- Core Mathematical Functions Implementation ---

    double N_pdf(double x) {
        // Standard Normal PDF: phi(x) = (1 / sqrt(2*pi)) * exp(-x^2 / 2)
        return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
    }

    double N_cdf(double x) {
        // Standard Normal CDF using the error function (std::erf).
        // Phi(x) = 0.5 * (1 + erf(x / sqrt(2)))
        return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
    }


    // --- Helper Functions (d1 and d2) Implementation ---
    
    void calculate_d1_d2(double S, double K, double T, double r, double sigma, 
                         double& d1, double& d2) 
    {
        if (T <= 0.0 || sigma <= 0.0) {
            // Handle edge cases to avoid division by zero
            d1 = (S > K) ? 100.0 : -100.0;
            d2 = d1;
            return;
        }

        double sigma_sqrt_T = sigma * std::sqrt(T);
        
        // d1 = [ln(S/K) + (r + sigma^2 / 2) * T] / (sigma * sqrt(T))
        d1 = (std::log(S / K) + (r + sigma * sigma / 2.0) * T) / sigma_sqrt_T;
        d2 = d1 - sigma_sqrt_T;
    }

    // --- Analytic Greeks for European Options ---

    double deltaCall(double S, double K, double T, double r, double sigma) {
        double d1, d2;
        calculate_d1_d2(S, K, T, r, sigma, d1, d2);
        
        // Delta Call = Phi(d1)
        return N_cdf(d1);
    }

    double gammaCallPut(double S, double K, double T, double r, double sigma) {
        double d1, d2;
        calculate_d1_d2(S, K, T, r, sigma, d1, d2);

        double denominator = S * sigma * std::sqrt(T);
        if (denominator == 0.0) return 0.0; 
        
        // Gamma = phi(d1) / (S * sigma * sqrt(T))
        return N_pdf(d1) / denominator;
    }

    double vegaCallPut(double S, double K, double T, double r, double sigma) {
        double d1, d2;
        calculate_d1_d2(S, K, T, r, sigma, d1, d2);

        // Vega = S * sqrt(T) * phi(d1)
        return S * std::sqrt(T) * N_pdf(d1);
    }

}
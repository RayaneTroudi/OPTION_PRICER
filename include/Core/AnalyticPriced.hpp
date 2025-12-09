#ifndef ANALYTICPRICED_HPP
#define ANALYTICPRICED_HPP

/**
 * @brief Interface for options that have closed-form (analytical) solutions
 * for their Greeks (sensitivities) under the Black-Scholes model.
 */
class AnalyticPriced {

    public:

        virtual ~AnalyticPriced() = default;

        /**
         * @brief Calculates the analytical Delta.
         */
        virtual double getAnalyticDelta(double S, double sigma) const = 0; 
        
        /**
         * @brief Calculates the analytical Gamma.
         */
        virtual double getAnalyticGamma(double S, double sigma) const = 0;

        /**
         * @brief Calculates the analytical Vega.
         */
        virtual double getAnalyticVega(double S, double sigma) const = 0;

    };

#endif 
#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP  

#include "../Core/Option.hpp"

/**
 * @brief Abstract intermediate base class for European-style options (vanilla and some exotics).
 * * It inherits time-to-maturity (T) and rate (r) and adds the Strike Price (K).
 * It remains abstract because the specific payoff logic (Call vs. Put) is not implemented here.
 */
class EuropeanOption : public Option {

    protected:

        /**
         * @brief The contractual price at which the asset can be bought or sold (Strike Price).
         */
        double K; 

    public:

        /**
         * @brief Constructor for the European option base class.
         * @param T_in Time to maturity, passed to Option base class.
         * @param r_in Risk-free rate, passed to Option base class.
         * @param K_in Strike Price.
         */
        EuropeanOption(double T_in, double r_in, double K_in): Option(T_in, r_in), K(K_in) {}

        /**
         * @brief Pure virtual payoff method inherited from Option.
         * It is redefined here to ensure all concrete European options implement it.
         * @param path The simulated price path.
         * @return The raw (undiscounted) payoff value.
         */
        virtual double payoff(const Path& path) const override = 0;

        /**
         * @brief Getter for the option's strike price.
         * @return The strike price K.
         */
        double getK() const { return K; }
        
};

#endif // EUROPEANOPTION_HPP
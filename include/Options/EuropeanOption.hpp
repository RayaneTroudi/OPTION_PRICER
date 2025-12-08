#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP  

#include "Core/Option.hpp"

class EuropeanOption : public Option {

    protected:

        double K; // Strike price

    public:
    
        // Constructor
        EuropeanOption(double T_in, double r_in, double K_in): Option(T_in, r_in), K(K_in) {}

        // virtual payoff method to be overridden by derived classes
        virtual double payoff(const Path& path) const override = 0;

        // Getter for strike price
        double getK() const { return K; }
};

#endif
#ifndef OPTION_HPP
#define OPTION_HPP

#include <cmath>
#include <vector>  
#include <iostream> 

#include "Core/Path.hpp"

class Option{

    protected: 

        double T;
        double r;

    public:
        
        // default constructor
        Option(double T_in, double r_in) : T(T_in), r(r_in) {}

        // default destructor
        virtual ~Option() = default;

        // virtual method for payoff calculation
        virtual double payoff(const Path& path) const = 0;

        // getters
        double getT() const { return T; }
        double getR() const { return r; }

        // discount factor calculation 
        double getDiscountFactor() const {
            return std::exp(-r * T);
        }

};

#endif
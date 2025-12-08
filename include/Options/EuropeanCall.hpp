#ifndef EUROPEANCALL_HPP
#define EUROPEANCALL_HPP    

#include "Options/EuropeanOption.hpp"
#include "Core/Path.hpp"

class EuropeanCall : public EuropeanOption {

    public:
    
        // Constructor
        EuropeanCall(double T_in, double r_in, double K_in);

        // Override payoff method
        virtual double payoff(const Path& path) const override;
};


#endif
#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "Options/EuropeanCall.hpp"
#include "Utils/BlackScholesFormulas.hpp" 
#include "Core/Path.hpp"



EuropeanCall::EuropeanCall(double T_in, double r_in, double K_in)
    : EuropeanOption(T_in, r_in, K_in) {}


double EuropeanCall::payoff(const Path& path) const {
    
    double S_T = path.getFinalPrice();
    
   
    return std::max(S_T - K, 0.0);
}

double EuropeanCall::getAnalyticDelta(double S, double sigma) const {
    // Delta Call = Phi(d1)
    return BlackScholesFormulas::deltaCall(S, getK(), getT(), getR(), sigma);
}

double EuropeanCall::getAnalyticGamma(double S, double sigma) const {
    // Gamma Call = Gamma Put
    return BlackScholesFormulas::gammaCallPut(S, getK(), getT(), getR(), sigma);
}

double EuropeanCall::getAnalyticVega(double S, double sigma) const {
    // Vega Call = Vega Put
    return BlackScholesFormulas::vegaCallPut(S, getK(), getT(), getR(), sigma);
}
#include "Options/EuropeanCall.hpp"
#include <algorithm> 

EuropeanCall::EuropeanCall(double T_in, double r_in, double K_in)
    : EuropeanOption(T_in, r_in, K_in) {}

double EuropeanCall::payoff(const Path& path) const {
    // 1. Get the final price S_T from the path
    double S_T = path.getFinalPrice();
    
    // 2. Return the maximum of (S_T - K) and zero
    // K (Strike) is accessible because it is 'protected' in the base class EuropeanOption.
    return std::max(S_T - K, 0.0);
}; 
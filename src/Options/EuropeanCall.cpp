#include "Options/EuropeanCall.hpp"
#include <algorithm>

EuropeanCall::EuropeanCall(double T_in, double r_in, double K_in)
    : EuropeanOption(T_in, r_in, K_in) {}


double EuropeanCall::payoff(const Path& path) const {
    double S_T = path.getFinalPrice();
    return std::max(S_T - K, 0.0);
};


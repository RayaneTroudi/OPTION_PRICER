#include "Options/AsianOption.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "Core/Path.hpp"


AsianOption::AsianOption(double T_in, double r_in, double K_in)
    : EuropeanOption(T_in, r_in, K_in) {}


double AsianOption::payoff(const Path& path) const {
    
    double S_average = path.getAveragePrice(); 
    
    return std::max(S_average - K, 0.0);
}
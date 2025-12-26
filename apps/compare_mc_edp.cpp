#include "PricingEngine/EDPSolver.hpp"
#include "PricingEngine/MonteCarloPricer.hpp"
#include "Options/EuropeanCall.hpp"
#include <iostream>

int main() {
    GBM gbm(100.0, 100, 0.05, 0.2);
    EuropeanCall call(1.0, 0.05, 100.0);

    // 1. Prix Monte Carlo
    MonteCarloPricer mc(call, gbm);
    auto res = mc.calculatePriceMinVar(10000);

    // 2. Prix EDP
    EDPSolver edp(call, gbm);
    double priceEDP = edp.solve(300.0, 100, 1000);

    std::cout << "Prix MC (MinVar): " << res.price << std::endl;
    std::cout << "Prix EDP:         " << priceEDP << std::endl;

    return 0;
}
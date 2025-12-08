#include "PricingEngine/MonteCarloPricer.hpp"
#include <numeric> // Required for accumulating sums if not using a simple loop
#include <cmath>   // Required for std::sqrt and std::pow (variance)

// --- Constructor Implementation ---

/**
 * @brief Constructs the Monte Carlo Pricer by linking to the Option and AssetModel interfaces.
 * * This allows the pricer to work generically with any concrete Option (Call, Put, Butterfly) 
 * and any AssetModel (GBM, Heston, etc.) through polymorphism.
 * @param option_in The option to be priced.
 * @param model_in The asset model to be used for path generation.
 */
MonteCarloPricer::MonteCarloPricer(const Option& option_in, const AssetModel& model_in)
    : option(option_in), model(model_in)
{}

// --- Pricing Method Implementation ---

/**
 * @brief Executes the Monte Carlo simulation to estimate the option price.
 * * The process involves generating paths, calculating payoffs, averaging, and discounting.
 * It also computes the Standard Error of the Mean (SEM) for confidence interval estimation.
 * @param num_simulations The number of paths to generate (N).
 * @return A PricingResult object containing the price, standard error, and payoff distribution.
 */
PricingResult MonteCarloPricer::calculatePrice(int num_simulations) const {
    
    std::vector<double> realized_payoffs;
    realized_payoffs.reserve(num_simulations);
    
    double sum_payoffs = 0.0;
    
    // Get the time to maturity (T) from the Option object
    double T = option.getT();

    // 1. Simulation Loop (The core Monte Carlo step)
    for (int i = 0; i < num_simulations; ++i) {
        
        // A. Generate the Path
        // Polymorphic call: uses the concrete model's generatePath() method (e.g., GBM)
        Path path = model.generatePath(T); 

        // B. Calculate the Payoff
        // Polymorphic call: uses the concrete option's payoff() method (e.g., EuropeanCall, Butterfly)
        double payoff = option.payoff(path);
        
        realized_payoffs.push_back(payoff);
        sum_payoffs += payoff;
    }

    // 2. Averaging and Discounting (Price Estimation)

    // Discount factor e^(-rT)
    double discount_factor = option.getDiscountFactor();
    
    // Mean Undiscounted Payoff (E[Payoff])
    double mean_payoff = sum_payoffs / num_simulations;
    
    // Option Price (V = e^(-rT) * E[Payoff])
    double price = discount_factor * mean_payoff;
    
    // 3. Standard Error Calculation (for Confidence Interval)
    
    // Calculate the variance of the payoffs (Var[Payoff])
    double sum_sq_diff = 0.0;
    for (double payoff : realized_payoffs) {
        // Deviation from the mean payoff
        double diff = payoff - mean_payoff;
        sum_sq_diff += diff * diff;
    }
    // Sample variance of the undiscounted payoffs (using N-1 for unbiased estimator)
    double payoff_variance = sum_sq_diff / (num_simulations - 1); 
    
    // Standard Error of the Mean (SEM)
    // SEM = [e^(-rT) * sqrt(Var(Payoff))] / sqrt(N)
    double standard_error = discount_factor * std::sqrt(payoff_variance / num_simulations);
    
    
    // 4. Return the Results
    return PricingResult(price, standard_error, realized_payoffs);
}
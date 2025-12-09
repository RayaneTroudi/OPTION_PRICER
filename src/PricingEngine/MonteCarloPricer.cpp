#include "PricingEngine/MonteCarloPricer.hpp"
#include "Models/GBM.hpp" 
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iostream>

MonteCarloPricer::MonteCarloPricer(const Option& option_in, const AssetModel& model_in)
    : option(option_in), model(model_in)
{}

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

PricingResult MonteCarloPricer::calculatePriceMinVar(int num_simulations) const {
    
    if (num_simulations % 2 != 0) {
        std::cerr << "Error: The number of simulations must be even for the Antithetic Variates method.\n";
        return PricingResult(0.0, 0.0, {});
    }
    
    // N_pairs is the number of independent samples (pairs)
    int num_pairs = num_simulations / 2; 
    
    // We only need to store the realized payoff averages for the true SEM calculation
    std::vector<double> paired_average_payoffs;
    paired_average_payoffs.reserve(num_pairs);
    
    double sum_payoffs = 0.0;
    double T = option.getT();

    // Downcast to GBM to access generateMinVarPaths
    const GBM* gbm_model = dynamic_cast<const GBM*>(&model);
    if (!gbm_model) {
        std::cerr << "Error: The MinVar method requires a GBM model (or an implementation of generateMinVarPaths).\n";
        return PricingResult(0.0, 0.0, {});
    }

    // 1. Simulation Loop (N/2 iterations)
    for (int i = 0; i < num_pairs; ++i) {
        
        // Generate the pair of paths (Path_i and Path'_i)
        std::pair<Path, Path> path_pair = gbm_model->generateMinVarPaths(T); 
        
        double payoff_std = option.payoff(path_pair.first);
        double payoff_anti = option.payoff(path_pair.second);
        
        // Calculate the average payoff for the current pair
        double average_payoff_pair = (payoff_std + payoff_anti) / 2.0;

        // Store the average payoff for the SEM calculation
        paired_average_payoffs.push_back(average_payoff_pair);
        
        // Accumulate the total sum (which equals the sum of the averages)
        sum_payoffs += payoff_std + payoff_anti;
    }

    // 2. Discounting and Averaging (Price Estimation)

    double discount_factor = option.getDiscountFactor();
    
    // Mean Payoff (E[Payoff]) is the average of all N payoffs
    double mean_payoff = sum_payoffs / num_simulations;
    double price = discount_factor * mean_payoff;
    
    // 3. Correct Standard Error Calculation (SEM_AV)
    
    // The correct formula uses the variance of the paired averages:
    // Var(V_AV) = Var(Average_Payoff_Pair) / N_pairs

    // First, calculate the sum of squared differences from the mean (using paired averages)
    double sum_sq_diff_paired = 0.0;
    for (double avg_payoff : paired_average_payoffs) {
        // We use the overall mean_payoff (which is the sample mean of the paired averages)
        double diff = avg_payoff - mean_payoff; 
        sum_sq_diff_paired += diff * diff;
    }
    
    // Payoff Variance of the PAIRED AVERAGE (Var(Avg_Payoff_Pair))
    // We use N_pairs - 1 for unbiased estimator.
    double paired_payoff_variance = sum_sq_diff_paired / (num_pairs - 1); 
    
    // Standard Error of the Mean (SEM_AV)
    // SEM = [e^(-rT) * sqrt(Var(Avg_Payoff_Pair))] / sqrt(N_pairs)
    double standard_error = discount_factor * std::sqrt(paired_payoff_variance / num_pairs);
    
    // 4. Return the Results
    // NOTE: realized_payoffs is now incorrect (contains paired averages), so we return an empty vector for the distribution.
    // If you absolutely need the distribution, you must revert to storing all individual N payoffs.
    return PricingResult(price, standard_error, {}); // Returning empty distribution vector for simplicity
}
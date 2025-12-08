#include "Models/RNG.hpp"
#include <chrono> // Required for seeding the generator

// --- Constructor Implementation ---

/**
 * @brief Private constructor for the Singleton RNG class.
 * * It initializes the random number generation engine and distribution.
 * * The generator is seeded using a time-based value (chrono::high_resolution_clock) 
 * to ensure a unique starting point for the random sequence in each program execution.
 */
RNG::RNG() 
    : generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()), 
      // Initialize the normal distribution to be N(0, 1) (mean=0.0, std_dev=1.0).
      normal_dist(0.0, 1.0) 
{}

// --- Singleton Access Implementation ---

/**
 * @brief Provides the globally accessible, single instance of the RNG class.
 * * This uses the 'magic static' initialization (thread-safe since C++11).
 * @return A reference to the single RNG instance.
 */
RNG& RNG::getInstance() {
    // The instance is created on first access.
    static RNG instance;
    return instance;
}

// --- Generator Method Implementation ---

/**
 * @brief Generates a random number from the Standard Normal Distribution (N(0, 1)).
 * * It calls the normal distribution object, passing the internal Mersenne Twister engine 
 * to generate the underlying uniform random number.
 * @return A double representing the random variable Z.
 */
double RNG::getStandardNormal() {
    return normal_dist(generator);
}
#include "Models/RNG.hpp"
#include <chrono> // Required for seeding the generator

RNG::RNG() 
    : generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()), 
      // Initialize the normal distribution to be N(0, 1) (mean=0.0, std_dev=1.0).
      normal_dist(0.0, 1.0) 
{}

RNG& RNG::getInstance() {
    // The instance is created on first access.
    static RNG instance;
    return instance;
}

double RNG::getStandardNormal() {
    return normal_dist(generator);
}
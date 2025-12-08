#include "Models/RNG.hpp"
#include <chrono> // For seeding the generator

// --- Constructor Implementation ---

RNG::RNG() 
    // Seed the generator using the system clock for a unique sequence each run.
    // Use std::random_device for better seeding if preferred, but chrono is simple.
    : generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()), 
      // Initialize the normal distribution with mean (0.0) and standard deviation (1.0)
      normal_dist(0.0, 1.0) 
{}

// --- Singleton Access Implementation ---

RNG& RNG::getInstance() {
    // Static local variable ensures the object is created only once (thread-safe since C++11)
    static RNG instance;
    return instance;
}

// --- Generator Method Implementation ---

double RNG::getStandardNormal() {
    // Generate a number using the normal distribution object and the MT engine.
    return normal_dist(generator);
}
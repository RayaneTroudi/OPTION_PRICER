#ifndef RNG_HPP
#define RNG_HPP

#include <random>

/**
 * @brief Utility class for generating random numbers.
 * * Uses the Mersenne Twister engine and a normal distribution for standard normal variables.
 * * Implemented as a Singleton for easy, global access across the simulation, 
 * ensuring consistent random number generation.
 */
class RNG {

    public:

        /**
         * @brief Provides the single instance of the RNG class.
         */
        static RNG& getInstance();
     
        /**
         * @brief Generates a single random number drawn from a Standard Normal Distribution (N(0, 1)).
         * @return A double representing the random variable Z.
         */
        double getStandardNormal();

    private:

        /**
         * @brief Private Constructor (ensures only one instance can be created).
         * Initializes the random engine and distribution.
         */
        RNG();
        
        RNG(const RNG&) = delete;
        RNG& operator=(const RNG&) = delete;

        // Mersenne Twister Engine (good statistical properties and speed)
        std::mt19937 generator;

        // Normal Distribution for N(0, 1)
        std::normal_distribution<double> normal_dist;
};

#endif 
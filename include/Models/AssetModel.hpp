#ifndef ASSETMODEL_HPP
#define ASSETMODEL_HPP

#include "../Core/Path.hpp" // For the Path type

/**
 * @brief Abstract base class for asset price evolution models.
 * * It ensures that any concrete model (e.g., GBM, Heston) implements 
 * the necessary path generation method.
 */
class AssetModel {

    public:
        
        /**
         * @brief Base constructor for common parameters.
         * @param S0_in Initial asset price.
         * @param steps_in Number of discrete time steps in the simulation.
         */
        AssetModel(double S0_in, int steps_in);
        
        /**
         * @brief Virtual destructor.
         */
        virtual ~AssetModel() = default;

        /**
         * @brief Generates a single Path of prices S_t according to the model's rules.
         * Must be implemented by concrete derived classes (e.g., GBM, Heston).
         * @param T The option's time to maturity (needed to calculate time step dt = T/steps).
         * @return The Path object containing the simulated price sequence.
         */
        virtual Path generatePath(double T) const = 0;

        double getS0() const { return S0; }
        int getSteps() const { return steps; }

    protected:

        double S0;    // Initial price of the underlying asset
        int steps;    // Number of time steps in the simulation
};

#endif 
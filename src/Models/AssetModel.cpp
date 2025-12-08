#include "Models/AssetModel.hpp"

// --- Constructor Implementation ---

/**
 * @brief Constructor for the AssetModel abstract base class.
 * * It initializes the core asset simulation parameters (S0 and steps).
 * @param S0_in Initial asset price.
 * @param steps_in Number of discrete time steps.
 */
AssetModel::AssetModel(double S0_in, int steps_in)
    : S0(S0_in), steps(steps_in) 
{}

// NOTE: The pure virtual method generatePath() must be implemented 
// by concrete derived classes (like GBM.cpp) and is NOT defined here.
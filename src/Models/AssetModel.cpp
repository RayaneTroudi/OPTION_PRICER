#include "Models/AssetModel.hpp"


AssetModel::AssetModel(double S0_in, int steps_in)
    : S0(S0_in), steps(steps_in) 
{}

// NOTE: The pure virtual method generatePath() must be implemented 
// by concrete derived classes (like GBM.cpp) and is NOT defined here.
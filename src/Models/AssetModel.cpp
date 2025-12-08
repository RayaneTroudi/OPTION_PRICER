#include "Models/AssetModel.hpp"

// Le constructeur est la seule méthode non-virtuelle à implémenter ici.
// Il appelle le constructeur de la classe de base (Option) et 
// initialise les paramètres S0 et steps.
AssetModel::AssetModel(double S0_in, int steps_in)
    : S0(S0_in), steps(steps_in) 
{}

// NOTE : La méthode generatePath() n'est PAS implémentée ici car elle est
// déclarée comme virtuelle pure dans AssetModel.hpp.
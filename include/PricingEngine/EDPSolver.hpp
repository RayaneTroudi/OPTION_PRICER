#ifndef EDPSOLVER_HPP
#define EDPSOLVER_HPP

#include "../Core/Option.hpp"
#include "../Models/GBM.hpp"
#include <vector>

/**
 * @brief Solveur d'EDP pour le modèle de Black-Scholes.
 * Utilise la méthode des Différences Finies.
 */
class EDPSolver {

public:
    // On passe le modèle GBM pour récupérer mu (r) et sigma
    EDPSolver(const Option& option_in, const GBM& model_in);

    /**
     * @brief Résout l'EDP sur une grille [0, T] x [0, S_max]
     * @param S_max Prix maximum pour la grille (souvent 2*K ou 3*K)
     * @param M Nombre de pas d'espace
     * @param N Nombre de pas de temps
     * @return Le prix calculé à S0
     */
    double solve(double S_max, int M, int N) const;


    /**
     * @brief Calcule la courbe complète du prix de l'option par rapport à S.
     * @return Une paire contenant le vecteur des prix S et le vecteur des valeurs V.
     */
    std::pair<std::vector<double>, std::vector<double>> calculateEDPCurve(double S_max, int M, int N) const;

private:

    const Option& option;
    const GBM& model;

};

#endif
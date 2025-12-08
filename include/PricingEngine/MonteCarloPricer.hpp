#ifndef MONTECARLOPRICER_HPP
#define MONTECARLOPRICER_HPP

// Inclusion des interfaces abstraites et du résultat
#include "../Core/Option.hpp"
#include "../Models/AssetModel.hpp"
#include "PricingResult.hpp"

/**
 * @brief Le moteur de pricing utilisant la méthode de Monte Carlo.
 * Il est chargé d'exécuter les simulations et de calculer le prix actualisé.
 */
class MonteCarloPricer {
public:
    // --- Constructeur ---
    
    /**
     * @brief Construit le pricer en prenant des références aux interfaces abstraites.
     * @param option_in L'option à pricer (interface abstraite Option).
     * @param model_in Le modèle de simulation à utiliser (interface abstraite AssetModel).
     */
    MonteCarloPricer(const Option& option_in, const AssetModel& model_in);

    // --- Méthode de Pricing ---
    
    /**
     * @brief Lance la simulation de Monte Carlo.
     * @param num_simulations Nombre de trajectoires à générer.
     * @return Un objet PricingResult contenant le prix, l'erreur standard et la distribution.
     */
    PricingResult calculatePrice(int num_simulations) const;

private:
    // Les références (const) permettent au pricer de travailler avec n'importe quelle 
    // implémentation concrète d'Option ou d'AssetModel (polymorphisme).
    const Option& option;
    const AssetModel& model;
};

#endif // MONTECARLOPRICER_HPP
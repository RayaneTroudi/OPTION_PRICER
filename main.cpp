#include <iostream>
#include <memory>
#include <limits>
#include <iomanip>
#include <string>

// --- CORE & INTERFACES ---
#include "Core/Option.hpp"
#include "Core/AnalyticPriced.hpp"
#include "Core/Path.hpp"

// --- OPTIONS IMPLEMENTATIONS ---
#include "Options/EuropeanCall.hpp"
#include "Options/EuropeanPut.hpp"
#include "Options/EuropeanBullCallSpread.hpp"
#include "Options/EuropeanButterFly.hpp"
#include "Options/AsianOption.hpp"

// --- MODELS & ENGINES ---
#include "Models/GBM.hpp"
#include "Models/RNG.hpp"
#include "PricingEngine/MonteCarloPricer.hpp"
#include "PricingEngine/GreeksPricer.hpp"

// --- UTILS ---
#include "Utils/GnuplotExporter.hpp"

// --- FONCTIONS DE VALIDATION ---

/**
 * @brief Sécurise la saisie d'un nombre double positif.
 */
double getSafeDouble(const std::string& prompt, bool allowZero = false) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && (allowZero ? value >= 0 : value > 0)) {
            return value;
        }
        std::cout << "Erreur : Saisie invalide. Entrez un nombre " 
                  << (allowZero ? ">= 0." : "> 0.") << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Sécurise la saisie d'un entier dans une plage.
 */
int getSafeInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            return value;
        }
        std::cout << "Erreur : Choix invalide (entre " << min << " et " << max << ")." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// --- LOGIQUE DE SELECTION D'OPTION ---

std::unique_ptr<Option> createOption(double T, double r) {
    std::cout << "\n--- CHOIX DE L'INSTRUMENT ---" << std::endl;
    std::cout << "1. European Call" << std::endl;
    std::cout << "2. European Put" << std::endl;
    std::cout << "3. European Bull Call Spread (K1 < K2)" << std::endl;
    std::cout << "4. European Butterfly Spread" << std::endl;
    std::cout << "5. Asian Call (Moyenne Arithmetique)" << std::endl;
    
    int choice = getSafeInt("Selection : ", 1, 5);
    double K, K2;

    switch (choice) {
        case 1: 
            K = getSafeDouble(">> Strike K : ");
            return std::make_unique<EuropeanCall>(T, r, K);
        case 2: 
            K = getSafeDouble(">> Strike K : ");
            return std::make_unique<EuropeanPut>(T, r, K);
        case 3: 
            K = getSafeDouble(">> Strike K1 (achat) : ");
            K2 = getSafeDouble(">> Strike K2 (vente) : ");
            return std::make_unique<CallSpread>(T, r, K, K2); //
        case 4: {
            std::cout << "Un Butterfly nécessite trois strikes (K1 < K2 < K3)." << std::endl;
            double K1 = getSafeDouble(">> Strike K1 (bas) : ");
            double K2 = getSafeDouble(">> Strike K2 (milieu) : ");
            double K3 = getSafeDouble(">> Strike K3 (haut) : ");
            return std::make_unique<EuropeanButterFly>(T, r, K1, K2, K3);
        }
        case 5: 
            K = getSafeDouble(">> Strike K : ");
            return std::make_unique<AsianOption>(T, r, K); //
        default: return nullptr;
    }
}

// --- MAIN ---

int main() {
    std::cout << std::fixed << std::setprecision(5);
    RNG::getInstance(); // Initialisation du générateur

    std::cout << "================================================\n";
    std::cout << "        PRICER MULTI-OPTIONS INTERACTIF         \n";
    std::cout << "================================================\n";

    // 1. Paramètres financiers
    double S0 = getSafeDouble(">> Prix initial de l'actif (S0) : ");
    double r  = getSafeDouble(">> Taux sans risque (r) [ex: 0.05] : ", true);
    double sigma = getSafeDouble(">> Volatilite (sigma) [ex: 0.2] : ");
    double T  = getSafeDouble(">> Maturite (T en annees) : ");

    // 2. Instanciation de l'option (Polymorphisme)
    std::unique_ptr<Option> selectedOption = createOption(T, r); //

    // 3. Configuration du modèle GBM
    int steps = getSafeInt(">> Nombre de pas de temps (discretisation) : ", 1, 1000);
    GBM model(S0, steps, r, sigma); //

    // 4. Moteurs de pricing
    MonteCarloPricer pricer(*selectedOption, model); //
    GreeksPricer greeks_pricer(*selectedOption, model); //

    bool running = true;
    while (running) {
        std::cout << "\n---------------- MENU ACTIONS ----------------" << std::endl;
        std::cout << "1. Simulation Monte Carlo Standard" << std::endl;
        std::cout << "2. Simulation avec Reduction de Variance (Antithetique)" << std::endl;
        std::cout << "3. Calcul des Grecs (Delta / Gamma)" << std::endl;
        std::cout << "4. Generer Graphique de Trajectoire (PNG)" << std::endl;
        std::cout << "0. Quitter" << std::endl;
        
        int action = getSafeInt("Choix : ", 0, 4);

        if (action == 0) {
            running = false;
            continue;
        }

        if (action == 4) {
            std::cout << "Exportation vers ../output/trajectory.png..." << std::endl;
            GnuplotExporter::savePathPNG(model.generatePath(T), T, "trajectory.png"); //
            continue;
        }

        int n_sims = getSafeInt(">> Nombre de simulations : ", 100, 10000000);

        if (action == 1) {
            auto res = pricer.calculatePrice(n_sims); //
            std::cout << "\n[RESULTAT MC STANDARD]" << std::endl;
            std::cout << "Prix estime : " << res.price << std::endl; //
            std::cout << "Erreur standard : " << res.standard_error << std::endl;
            std::cout << "IC 95% : [" << res.confidenceInterval95Lower() << " ; " << res.confidenceInterval95Upper() << "]" << std::endl;
        } 
        else if (action == 2) {
            if (n_sims % 2 != 0) n_sims++; // Force un nombre pair pour les paires antitéthiques
            auto res = pricer.calculatePriceMinVar(n_sims); //
            std::cout << "\n[RESULTAT MC ANTITHETIQUE]" << std::endl;
            std::cout << "Prix estime : " << res.price << std::endl;
            std::cout << "Erreur standard : " << res.standard_error << " (Variance reduite)" << std::endl;
        } 
        else if (action == 3) {
            double eps = 0.01 * S0;
            double delta = greeks_pricer.calculateDelta(n_sims, eps); //
            double gamma = greeks_pricer.calculateGamma(n_sims, eps); //
            std::cout << "\n[SENSIBILITES (GREEKS)]" << std::endl;
            std::cout << "Delta : " << delta << std::endl;
            std::cout << "Gamma : " << gamma << std::endl;
        }
    }

    std::cout << "\nFermeture du programme. Bonne journee !" << std::endl;
    return 0;
}
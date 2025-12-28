#ifndef GNUPLOTEXPORTER_HPP
#define GNUPLOTEXPORTER_HPP

#include <string>
#include <vector>
#include "../Core/Path.hpp"

class GnuplotExporter {
public:
    // Exporte une trajectoire simple en PNG
    static void savePathPNG(const Path& path, double T, const std::string& filename);

    // Exporte la convergence : itération vs prix moyen (Standard vs MinVar)
    static void saveConvergencePNG(const std::vector<double>& standardPrices, 
                                 const std::vector<double>& minVarPrices, 
                                 const std::string& filename);

    /**
     * @brief Génère un graphique du prix de l'option en fonction du prix de l'actif (S) à partir des données EDP.
     * @param s_values Vecteur des prix de l'actif (abscisses)
     * @param v_values Vecteur des prix de l'option calculés (ordonnées)
     * @param filename Nom du fichier PNG de sortie (ex: "edp_curve.png")
     */
    static void saveEDPCurvePNG(const std::vector<double>& s_values, 
                               const std::vector<double>& v_values, 
                               const std::string& filename);
};

#endif
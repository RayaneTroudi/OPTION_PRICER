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
};

#endif
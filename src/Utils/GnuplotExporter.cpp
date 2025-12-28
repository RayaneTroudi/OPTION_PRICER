#include "Utils/GnuplotExporter.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

// Inclusion robuste pour filesystem
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#endif

void GnuplotExporter::savePathPNG(const Path& path, double T, const std::string& filename) {
    // Utilisation de "../output" pour sortir du dossier build
    fs::create_directories("../output"); 
    
    std::string dataPath = "../output/path_data.dat";
    std::string scriptPath = "../output/render_path.gp";

    std::ofstream df(dataPath);
    if (!df.is_open()) return;

    double dt = T / (path.getLength() - 1);
    for(size_t i = 0; i < path.getLength(); ++i) {
        df << i * dt << "\t" << path.at(i) << "\n";
    }
    df.close();

    std::ofstream sf(scriptPath);
    if (!sf.is_open()) return;

    sf << "set terminal pngcairo size 800,600\n";
    sf << "set output '../output/" << filename << "'\n"; // Cible la racine
    sf << "set title 'Asset Price Trajectory'\n";
    sf << "set grid\n";
    sf << "plot '" << dataPath << "' with lines title 'S_t'\n";
    sf.close();

    // Exécution du script via gnuplot
    std::system("gnuplot ../output/render_path.gp");
}

void GnuplotExporter::saveConvergencePNG(const std::vector<double>& stdP, 
                                       const std::vector<double>& minP, 
                                       const std::string& filename) {
    // Utilisation de "../output"
    fs::create_directories("../output");
    
    std::ofstream df("../output/conv_data.dat");
    for(size_t i = 0; i < stdP.size(); ++i) {
        df << i << "\t" << stdP[i] << "\t" << minP[i] << "\n";
    }
    df.close();

    std::ofstream sf("../output/render_conv.gp");
    sf << "set terminal pngcairo size 800,600\n";
    sf << "set output '../output/" << filename << "'\n";
    sf << "set title 'Convergence: Standard vs Antithetic'\n";
    sf << "plot '../output/conv_data.dat' u 1:2 w l title 'Standard MC', "
       << "'../output/conv_data.dat' u 1:3 w l title 'Min Var MC'\n";
    sf.close();

    std::system("gnuplot ../output/render_conv.gp");
}

void GnuplotExporter::saveEDPCurvePNG(const std::vector<double>& s_values, 
                                     const std::vector<double>& v_values, 
                                     const std::string& filename) {
    std::string folder = "../output/";
    
    // 1. Écriture des données
    std::ofstream dataFile(folder + "edp_data.dat");
    if (!dataFile.is_open()) return; // Sécurité simple
    
    for (size_t i = 0; i < s_values.size(); ++i) {
        dataFile << s_values[i] << " " << v_values[i] << "\n";
    }
    dataFile.close();

    // 2. Écriture du script Gnuplot
    std::ofstream scriptFile(folder + "plot_edp.gp");
    if (!scriptFile.is_open()) return;

    scriptFile << "set terminal pngcairo\n";
    scriptFile << "set output \"" << folder << filename << "\"\n"; // Utilisation de guillemets doubles
    
    // CORRECTION : Utilisation de \" pour inclure l'apostrophe dans le titre
    scriptFile << "set title \"Prix de l'option via EDP (t=0)\"\n"; 
    
    scriptFile << "set xlabel \"Prix de l'actif (S)\"\n";
    scriptFile << "set ylabel \"Valeur de l'option (V)\"\n";
    scriptFile << "set grid\n"; // Optionnel : ajoute une grille pour la lisibilité
    
    scriptFile << "plot \"" << folder << "edp_data.dat\" with lines lw 2 lc rgb 'blue' title \"Solution EDP\"\n";
    scriptFile.close();

    // 3. Exécution de Gnuplot
    // Utilisation de guillemets pour le chemin du script au cas où il y aurait des espaces
    std::string command = "gnuplot \"" + folder + "plot_edp.gp\"";
    std::system(command.c_str());
}
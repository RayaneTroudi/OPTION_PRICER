cmake_minimum_required(VERSION 3.10)
project(OptionPricer LANGUAGES CXX)

# --- 1. CONFIGURATION DU COMPILATEUR (Spécifique macOS) ---
if(APPLE)
    # Débloque std::filesystem sur macOS
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- 2. CONFIGURATION DE LA BIBLIOTHÈQUE ---
# Inclut tous les .cpp du dossier src/ pour créer la lib métier
include_directories(include) 
file(GLOB_RECURSE PRICER_LIB_SRC "src/*.cpp")

add_library(pricer_lib ${PRICER_LIB_SRC}) 
target_include_directories(pricer_lib PUBLIC include) 

# --- 3. DÉFINITION DES EXÉCUTABLES ---

# A. Pricing classique
add_executable(pricer_test main.cpp)
target_link_libraries(pricer_test pricer_lib)

# B. Tracé de trajectoire (nécessite apps/plot_path.cpp)
add_executable(plot_path apps/plot_path.cpp)
target_link_libraries(plot_path pricer_lib)

# C. Convergence et Réduction de Variance (nécessite apps/show_convergence.cpp)
add_executable(show_convergence apps/show_convergence.cpp)
target_link_libraries(show_convergence pricer_lib)

add_executable(compare_mc_edp apps/compare_mc_edp.cpp)
target_link_libraries(compare_mc_edp pricer_lib)
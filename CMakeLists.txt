cmake_minimum_required(VERSION 3.10)

project(OptionPricer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Configuration du code métier (Bibliothèque statique) ---

include_directories(include)

# Récupère tous les fichiers .cpp dans src/ et ses sous-dossiers
# NOTE: Cette forme est plus robuste pour la récursion
file(GLOB_RECURSE PRICER_LIB_SRC 
    "src/*.cpp"
    "src/Options/*.cpp"
    "src/PricingEngine/*.cpp"
    "src/Utils/*.cpp"
)

# Crée la bibliothèque statique qui contient tout le code source, y compris BlackScholesFormulas.cpp
add_library(pricer_lib ${PRICER_LIB_SRC}) 

# Définit le chemin d'inclusion pour la bibliothèque (nécessaire si vous utilisez cette bibliothèque ailleurs)
target_include_directories(pricer_lib PUBLIC include) 


# --- Définition de l'Exécutable Principal (pricer_test) ---

# L'exécutable a seulement besoin de main.cpp
add_executable(pricer_test main.cpp)

# Lie l'exécutable à la bibliothèque pricer_lib
target_link_libraries(pricer_test pricer_lib)

# --- (Ici, vous ajouteriez la configuration de GTest, si nécessaire) ---
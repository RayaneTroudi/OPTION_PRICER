cmake_minimum_required(VERSION 3.10)

project(OptionPricer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- 1. Configuration du code métier (Bibliothèque statique) ---

# Inclut le répertoire 'include/' pour que le compilateur trouve les en-têtes
include_directories(include) 

# Utilisation de GLOB_RECURSE pour capturer TOUS les fichiers .cpp 
# dans le dossier 'src/' et tous ses sous-dossiers (Options, PricingEngine, Utils, etc.)
file(GLOB_RECURSE PRICER_LIB_SRC "src/*.cpp")

# Crée la bibliothèque statique 'pricer_lib' à partir de tous les fichiers sources trouvés
add_library(pricer_lib ${PRICER_LIB_SRC}) 

# Définit le chemin d'inclusion pour la bibliothèque 
target_include_directories(pricer_lib PUBLIC include) 


# --- 2. Définition de l'Exécutable Principal (pricer_test) ---

# L'exécutable utilise uniquement main.cpp comme point d'entrée
add_executable(pricer_test main.cpp)

# Lie l'exécutable à la bibliothèque pricer_lib
# Ceci est crucial : cela garantit que tous les symboles de vos classes (.cpp) sont trouvés
target_link_libraries(pricer_test pricer_lib)

# --- 3. Configuration des Tests (Optionnel, mais bonne pratique) ---
# Vous pouvez réutiliser pricer_lib pour lier les tests GTest

# if(EXISTS "tests")
#     add_subdirectory(vendor/googletest)
#     enable_testing()
# 
#     add_executable(run_tests tests/test_myoption.cpp)
#     target_link_libraries(run_tests pricer_lib GTest::gtest_main)
#     add_test(NAME MyTests COMMAND run_tests)
# endif()
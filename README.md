========================================================================
             OPTIONPRICER - PLATEFORME DE PRICING DE DERIVES
========================================================================

1. DESCRIPTION DU PROJET
------------------------
OptionPricer est un moteur de calcul financier performant développé en C++.
Il permet d'évaluer le prix d'options vanilles et exotiques en utilisant :
  * Des simulations de Monte Carlo (Mouvement Brownien Géométrique).
  * Des techniques de réduction de variance (Variables Antithétiques).
  * Des méthodes numériques déterministes (Solveur EDP).
  * Le calcul des Grecques (Delta, Gamma) par différences finies.

2. INSTRUMENTS SUPPORTES
------------------------
Grâce à une architecture basée sur le polymorphisme, le programme gère :
  * European Call & Put : Options vanilles classiques.
  * Bull Call Spread : Stratégie à deux strikes (K1 < K2).
  * Butterfly Spread : Stratégie à trois strikes (K1 < K2 < K3).
  * Asian Option : Option exotique sur moyenne arithmétique.

3. PREREQUIS SYSTEME
--------------------
  * Compilateur : Supportant le standard C++17 (AppleClang ou GCC).
  * Build System : CMake (version 3.10 ou supérieure).
  * Graphiques : Gnuplot installé pour la génération de PNG.

4. PROCEDURE DE LANCEMENT (COMPILATION)
---------------------------------------
Ouvrez un terminal à la racine du projet et exécutez :

  mkdir build && cd build
  cmake ..
  make

5. EXECUTION DES OUTILS
-----------------------
Une fois la compilation terminée, trois outils sont disponibles :

  A. Interface Interactive :
     ./pricer_test
     (Permet de configurer S0, r, sigma, T et de choisir l'option).

  B. Etude de Convergence :
     ./show_convergence
     (Génère un graphique comparant MC Standard vs Antithetic).

  C. Comparaison MC vs EDP :
     ./compare_mc_edp
     (Étude asymptotique entre approche stochastique et numérique).

6. NOTES TECHNIQUES
-------------------
  * Sortie : Les graphiques sont générés dans le dossier "output/".
  * Securite : L'interface valide les entrées pour éviter les erreurs de calcul.
  * Stabilite EDP : Veillez à un nombre de pas de temps suffisant (N) par 
    rapport aux pas d'espace (M) pour la convergence du schéma.
  * RNG : Utilisation du générateur Mersenne Twister (mt19937).

------------------------------------------------------------------------
Développé par Rayane Troudi - Projet C++ ENSAE
========================================================================
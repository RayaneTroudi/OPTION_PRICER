set terminal pngcairo size 800,600
set output '../output/convergence_asian.png'
set title 'Convergence: Standard vs Antithetic'
plot '../output/conv_data.dat' u 1:2 w l title 'Standard MC', '../output/conv_data.dat' u 1:3 w l title 'Min Var MC'

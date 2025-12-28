set terminal pngcairo
set output "../output/edp_option_price.png"
set title "Prix de l'option via EDP (t=0)"
set xlabel "Prix de l'actif (S)"
set ylabel "Valeur de l'option (V)"
set grid
plot "../output/edp_data.dat" with lines lw 2 lc rgb 'blue' title "Solution EDP"

set terminal pngcairo size 800,600
set output '../output/path.png'
set title 'Asset Price Trajectory'
set grid
plot '../output/path_data.dat' with lines title 'S_t'

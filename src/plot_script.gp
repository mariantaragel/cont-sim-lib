set terminal pngcairo enhanced font "Arial,12" size 800,600
set output "simulation_plot.png"

set title "Kruhový test"
set xlabel "x"
set ylabel "y"
set grid
set key left top

plot "ab4.txt" using 2:3 with lines title "Adams-Bashforth 4th" lt rgb "blue"
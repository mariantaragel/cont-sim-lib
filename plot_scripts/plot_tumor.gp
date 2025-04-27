set terminal pngcairo enhanced font "Arial,15" size 1000,400
set output "tumor_ab4_1.png"

set title "Tumor model, method=Adams-Bashforth 4th, h=0.1"
set xlabel "Time t [days]"
set ylabel "Cell population"
set grid
set key top right

plot "simulation_data.txt" using 1:2 with lines title "T_I (interphase)" lt rgb "red" lw 2, \
     "simulation_data.txt" using 1:3 with lines title "T_M (mitosis)" lt rgb "blue" lw 2, \
     "simulation_data.txt" using 1:4 with lines title "I (immune cells)" lt rgb "green" lw 2

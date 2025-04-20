set terminal pngcairo enhanced font "Arial,12" size 700,700
set output "ab4_0.1_plot.png"

set title "Circular test"
set xlabel "x"
set ylabel "y"
set grid
set key left top

plot "ab4_0.1_data.txt" using 2:3 with lines title "AB4 (0.1)" lt rgb "red", \
     "ab4_0.1_data.txt" using 4:5 with lines title "Analytical solution" lt rgb "blue"

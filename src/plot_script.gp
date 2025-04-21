set terminal pngcairo enhanced font "Arial,12" size 1000,600
set output "tumor_simulation_plot.png"

set title "Population of tumor and immune cells"
set xlabel "Time [days]"
set ylabel "Cell population"
set grid
set key right top

plot "simulation_data.txt" using 1:2 with lines title "Tumor cell population during interphase (T_I)" lt rgb "red", \
     "simulation_data.txt" using 1:3 with lines title "Tumor cell population during mitosis (T_M)" lt rgb "blue", \
     "simulation_data.txt" using 1:4 with lines title "Immune system population (I)" lt rgb "green"

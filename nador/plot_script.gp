set terminal pngcairo enhanced font "Arial,12" size 800,600
set output "tumor_simulation_plot.png"

set title "Dynamika nádoru, imunitnej odpovede a liečby"
set xlabel "Čas (t)"
set ylabel "Populácia buniek / Koncentrácia lieku"
set grid
set key right top

plot "tumor_simulation_data.txt" using 1:2 with lines title "Interfázové nádorové bunky (T_I)" lt rgb "red", \
     "tumor_simulation_data.txt" using 1:3 with lines title "Mitotické nádorové bunky (T_M)" lt rgb "blue", \
     "tumor_simulation_data.txt" using 1:4 with lines title "Imunitný systém (I)" lt rgb "green", \
     "tumor_simulation_data.txt" using 1:5 with lines title "Koncentrácia lieku (u)" lt rgb "purple"

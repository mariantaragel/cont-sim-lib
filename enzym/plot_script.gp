set terminal pngcairo enhanced font "Arial,14" size 1000,700
set output "enzyme_kinetics_zoomed.png"

set title "Simulácia enzýmovej kinetiky"
set xlabel "Čas (t)"
set ylabel "Koncentrácia"
set grid
set key right top

# Prvý graf - celý priebeh
set multiplot layout 2,1 title "Simulácia enzýmovej kinetiky - Celý priebeh a detail začiatku"

plot "simulation_data.txt" using 1:2 with lines title "Substrát (s)" lt rgb "red", \
     "simulation_data.txt" using 1:3 with lines title "Enzým (e)" lt rgb "green", \
     "simulation_data.txt" using 1:4 with lines title "Produkt (p)" lt rgb "blue"

# Druhý graf - len detail začiatku
set xrange [0:2]  # Zoom na prvé sekundy
set title "Detail začiatku reakcie"
plot "simulation_data.txt" using 1:2 with lines title "Substrát (s)" lt rgb "red", \
     "simulation_data.txt" using 1:3 with lines title "Enzým (e)" lt rgb "green", \
     "simulation_data.txt" using 1:4 with lines title "Produkt (p)" lt rgb "blue"

unset multiplot

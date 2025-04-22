set terminal pngcairo enhanced font "Arial,12" size 1000,800
set output "hiv_simulation_plot2.png"

set multiplot layout 2,2 title "HIV model, method=rk4, h=0.001"

# 1. T (target cells - CD4+)
set xlabel "Time t"
set ylabel "Target Cells"
plot "simulation_data.txt" using 1:5 with lines title "T(t)" lt rgb "orange"

# 2. V (virions)
set xlabel "Time t"
set ylabel "Virus"
plot "simulation_data.txt" using 1:4 with lines title "V(t)" lt rgb "dark-green"

# 3. I (virus-producing cells)
set xlabel "Time t"
set ylabel "Infectious Cells"
plot "simulation_data.txt" using 1:3 with lines title "I(t)" lt rgb "red"

# 4. IE (eclipse phase cells)
set xlabel "Time t"
set ylabel "Eclipse Cells"
plot "simulation_data.txt" using 1:2 with lines title "IE(t)" lt rgb "blue"

unset multiplot

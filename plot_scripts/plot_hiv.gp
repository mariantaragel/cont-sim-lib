set terminal pngcairo enhanced font "Arial,15" size 1000,600
set output "hiv_euler_01.png"

set multiplot layout 2,2 title "HIV model, method=Euler, h=0.01"

# 1. T (target cells - CD4+)
set xlabel "Time t"
set ylabel "Target Cells"
# set yrange [0:2200]
# set ytics ("0" 0, "550" 550, "1100" 1100, "1650" 1650, "2200" 2200)
plot "simulation_data.txt" using 1:5 with lines title "T(t)" lt rgb "orange" lw 2

# 2. V (virions)
set xlabel "Time t"
set ylabel "Virus"
# set yrange [0:18000]
# set ytics ("0" 0, "4500" 4500, "9000" 9000, "13500" 13500, "18000" 18000)
plot "simulation_data.txt" using 1:4 with lines title "V(t)" lt rgb "dark-green" lw 2

# 3. I (virus-producing cells)
set xlabel "Time t"
set ylabel "Infectious Cells"
# unset yrange
# set ytics auto
plot "simulation_data.txt" using 1:3 with lines title "I(t)" lt rgb "red" lw 2

# 4. IE (eclipse phase cells)
set xlabel "Time t"
set ylabel "Eclipse Cells"
plot "simulation_data.txt" using 1:2 with lines title "IE(t)" lt rgb "blue" lw 2

unset multiplot

set terminal pngcairo size 800,600
set output "tank_path.png"
set title "Tank trajectory"
set xlabel "x [m]"
set ylabel "y [m]"
plot "simulation_data.txt" using 5:6 with lines title "Tank path" lw 2

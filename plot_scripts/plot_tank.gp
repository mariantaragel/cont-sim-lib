set terminal pngcairo enhanced font "Arial,8" size 300,300
set output "tank_rk4_001.png"
set title "Tank model, method=Runge-Kutta 4th, h=0.001"
set xlabel "x [m]"
set ylabel "y [m]"
plot "simulation_data.txt" using 5:6 with lines title "Tank path" lw 2

############################################################################
# GnuPlot script for model ball
#
reset  # defaults

#set output "example.ps"; set term postscript

set style data lines
#set grid

set title "Projectile"
set key
set xlabel "Distance [m]"
set ylabel "Height [m]"
plot "simulation.dat" using 3:2 title "Projectile height", 0 notitle with dots
pause 1

#end

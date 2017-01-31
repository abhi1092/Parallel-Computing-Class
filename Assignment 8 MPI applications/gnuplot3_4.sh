#!/usr/bin/gnuplot
reset
set term png
set xlabel "Number of Process" 
set ylabel "Speedup"
set title name3
set output name2
plot name index 0 using 1:2 title 'Array Size 1GB' with linespoints, '' index 1 using 1:2 title 'Array Size 20GB' with linespoints, '' index 2 using 1:2 title 'Array Size 80GB' with linespoints

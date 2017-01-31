#!/usr/bin/gnuplot
reset
set term png
set xlabel "Number of Process" 
set ylabel "Speedup"
set title name3
set output name2
plot name index 0 using 1:2 title 'Operation Intensity 10' with linespoints, '' index 1 using 1:2 title 'Operation Intensity 1000' with linespoints

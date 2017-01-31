#!/usr/bin/gnuplot

reset
set term png

set title name3
set output name2

plot name index 0 using 1:2 title 'Dynamic 1' with linespoints, '' index 1 using 1:2 title 'Dynamic 1000' with linespoints



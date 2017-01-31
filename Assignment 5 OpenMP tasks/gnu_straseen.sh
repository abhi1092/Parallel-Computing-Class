#!/usr/bin/gnuplot

reset
set term png

set title name3
set output name2
set logscale x 10
plot name index 0 using 1:2 title 'Speedup with 16 threads' with linespoints


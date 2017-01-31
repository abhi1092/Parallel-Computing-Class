#!/usr/bin/gnuplot

reset
set term png

set title name3
set output name2
plot name index 0 using 1:2 title 'Array size of 10^9' with linespoints

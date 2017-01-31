#!/usr/bin/gnuplot
reset
set term png
set xrange[0:1000000000]
set yrange[-5:5]
set output './task_data/task_speedup_chart.png'
plot './task_data/task_data.dat' with linespoints 

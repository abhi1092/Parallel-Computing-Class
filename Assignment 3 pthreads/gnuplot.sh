#!/usr/bin/gnuplot
#
# Plotting the data of file data.dat with points and non-continuous lines
#
# AUTHOR: Hagen Wierstorf
# VERSION: gnuplot 4.6 patchlevel 0

reset

# wxt
#set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
# png
#set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
#set output 'non-continuous_lines.png'
set term png
# color definitions
#set border linewidth 1.5
#set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5
#set pointintervalbox 1

#unset key

#set ytics 1
#set ytics 1
#set tics scale 0.1

#set xrange [0:20]
#set yrange [0:20]
set output name2
plot name with linespoints ls 1

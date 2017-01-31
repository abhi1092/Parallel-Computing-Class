set title 'Example Plot'
set ylabel'Execution time in Seconds'
set xlabel'Number of Search integers'
set grid
set term png
set output "graph.png"
plot 'data.dat'
set term x11


set term png
set output 'ratio_vary.png'
set logscale x 10

plot 'ratio_vary.txt' with linespoints

#!/bin/bash
g++ Prefix_sum.c -fopenmp -o prefix_sum


mode=1
num_thrd=0
array_size=1073741824
sequential_time=`./prefix_sum $num_thrd $array_size $mode`
mode=2
echo >plot_prefix_sum.dat
for((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./prefix_sum $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_prefix_sum.dat
done

gnuplot -e "name='plot_prefix_sum.dat';name2='plot_prefix_sum.png';name3='Speedup chart for Prefix Sum'" gnuplot2.sh

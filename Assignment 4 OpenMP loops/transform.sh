#!/bin/bash
g++ transform_s.c -fopenmp -o transform_s
array_size=100000000
num_thrd=0
mode=1
sequential_time=`./transform_s $num_thrd $array_size $mode`
mode=2
echo >plot_transform_data.dat
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./transform_s $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_transform_data.dat
done

echo >>plot_transform_data.dat
echo >>plot_transform_data.dat
mode=3
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./transform_s $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_transform_data.dat
done


echo >>plot_transform_data.dat
echo >>plot_transform_data.dat
mode=4
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./transform_s $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_transform_data.dat
done


echo >>plot_transform_data.dat
echo >>plot_transform_data.dat
mode=5
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./transform_s $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_transform_data.dat
done

gnuplot -e "name='plot_transform_data.dat';name2='plot_transform_data.png';name3='Speedup chart for Transform'" gnuplot.sh


g++ merge_sort.c -fopenmp -o merge_sort

mode=1
num_thrd=0
array_size=1073741824
sequential_time=`./merge_sort $num_thrd $array_size $mode`
mode=2
echo >plot_merge_sort.dat
for((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./merge_sort $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$paralle_time"|bc -l)>>plot_merge_sort.dat
done

gnuplot -e "name='plot_merge_sort.dat';name2='plot_merge_sort.png';name3='Speedup chart for Merge Sort'" gnuplot2.sh


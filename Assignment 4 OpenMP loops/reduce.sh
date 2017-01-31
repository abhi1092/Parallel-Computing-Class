g++ reduce_s.c -fopenmp -o reduce 
thread_num=0
array_size=100000000
num_thrd=0
mode=1
sequential_time=`./reduce $num_thrd $array_size $mode`
mode=2
echo >plot_reduce_data.dat
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./reduce $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_reduce_data.dat
done

echo >>plot_reduce_data.dat
echo >>plot_reduce_data.dat
mode=3
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./reduce $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_reduce_data.dat
done


echo >>plot_reduce_data.dat
echo >>plot_reduce_data.dat
mode=4
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./reduce $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_reduce_data.dat
done

echo >>plot_reduce_data.dat
echo >>plot_reduce_data.dat
mode=5
for ((num_thrd=1;num_thrd<=16;num_thrd=num_thrd*2));do
	parallel_time=`./reduce $num_thrd $array_size $mode`
	echo $num_thrd $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_reduce_data.dat
done

gnuplot -e "name='plot_reduce_data.dat';name2='plot_reduce_data.png';name3='Speedup chart for Reduce'" gnuplot.sh

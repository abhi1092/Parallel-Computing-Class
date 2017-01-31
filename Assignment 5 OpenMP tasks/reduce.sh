g++ reduce.c -fopenmp -o reduce

array=100000000
sequential=`./reduce 0 $array 1 0 0`
echo >reduce_plot_static.dat

for((granularity=1000;granularity<=100000;granularity=granularity*100));do
	for((num_thrds=1;num_thrds<=16;num_thrds=num_thrds*2));do
	parallel=`./reduce $num_thrds $array 2 $granularity 1`
	echo $num_thrds $(echo $sequential/$parallel|bc -l)>>reduce_plot_static.dat
	done
	echo >>reduce_plot_static.dat
	echo >>reduce_plot_static.dat
done

gnuplot -e "name='reduce_plot_static.dat';name2='reduce_plot_static.png';name3='Reduce Speedup chart for static schedule'" gnu_reduce.sh 

echo >reduce_plot_dynamic_1.dat
for((granularity=1000;granularity<=100000;granularity=granularity*100));do
	for((num_thrds=1;num_thrds<=16;num_thrds=num_thrds*2));do
	parallel=`./reduce $num_thrds $array 2 $granularity 2`
	echo $num_thrds $(echo $sequential/$parallel|bc -l)>>reduce_plot_dynamic_1.dat
	done
	echo >>reduce_plot_dynamic_1.dat
	echo >>reduce_plot_dynamic_1.dat
done

gnuplot -e "name='reduce_plot_dynamic_1.dat';name2='reduce_plot_dynamic_1.png';name3='Reduce Speedup chart for Dynamic 1 schedule'" gnu_reduce.sh 


echo >reduce_plot_dynamic_10000.dat
for((granularity=1000;granularity<=100000;granularity=granularity*100));do
	for((num_thrds=1;num_thrds<=16;num_thrds=num_thrds*2));do
	parallel=`./reduce $num_thrds $array 2 $granularity 3`
	echo $num_thrds $(echo $sequential/$parallel|bc -l)>>reduce_plot_dynamic_10000.dat
	done
	echo >>reduce_plot_dynamic_10000.dat
	echo >>reduce_plot_dynamic_10000.dat
done

gnuplot -e "name='reduce_plot_dynamic_10000.dat';name2='reduce_plot_dynamic_10000.png';name3='Reduce Speedup chart for Dynamic 1000 schedule'" gnu_reduce.sh 



g++ merge_sort.c -fopenmp -o merge_sort

array=1000000000
sequential=`./merge_sort 0 $array 1`
echo >Merge_sort_plot.dat
for((num_thrds=1;num_thrds<=16;num_thrds=num_thrds*2));do
	parallel=`./merge_sort $num_thrds $array 2`
	echo $num_thrds $(echo $sequential/$parallel|bc -l)>>Merge_sort_plot.dat
done
gnuplot -e "name='Merge_sort_plot.dat';name2='Merge_sort_plot.png';name3='Merge_sort Speedup chart'" gnu_merge_sort.sh 

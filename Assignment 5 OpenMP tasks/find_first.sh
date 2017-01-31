g++ find_first.c -fopenmp -o find_first

array=100000000
granularity=100000
sequential=`./find_first 0 $array 1 $granularity`
echo >Find_First_plot.dat
for((num_thrds=1;num_thrds<=16;num_thrds=num_thrds*2));do
	parallel=`./find_first $num_thrds $array 2 $granularity`
	echo $num_thrds $(echo $sequential/$parallel|bc -l)>>Find_First_plot.dat
done
gnuplot -e "name='Find_First_plot.dat';name2='Find_First_plot.png';name3='Find first Speedup chart'" gnu_Find_first.sh 

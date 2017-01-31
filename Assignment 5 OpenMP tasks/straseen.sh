g++ straseen.c -fopenmp -Wno-write-strings -o straseen

sequential=`./straseen 16 10000 1`
parallel=`./straseen 16 10000 2`
numer_of_threads=16
echo >strassen_plot.dat
for((operation_intensity=100;operation_intensity<1000000;operation_intensity=operation_intensity*10));do
	sequential=`./straseen $numer_of_threads $operation_intensity 1`
	parallel=`./straseen $numer_of_threads $operation_intensity 2`
	echo $operation_intensity $(echo $sequential/$parallel|bc -l)>>strassen_plot.dat
done

gnuplot -e "name='strassen_plot.dat';name2='strassen_plot.png';name3='Mock straseen speedup chart'" gnu_straseen.sh 

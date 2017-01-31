mpicc numerical_integration3.c -o numerical_integration3
g++ numerical_integration_sequential.c -o  numerical_integration_sequential
a=1
b=500
N=1000000000
op=1000
sequential_time=0
Chunk_size=1000
for((N=10;N<=100000000;N=N*10));do
    echo>plot_data_points_${N}.dat
    for((op=10;op<=1000;op=op*100));do
	sequential_time=`./numerical_integration_sequential $a $b $N $op`
	for((process=2;process<=32;process=process*2));do
	    parallel_time=`mpirun -n $process ./numerical_integration3 $a $b $N $op $Chunk_size`
	    echo $process $(echo $sequential_time/$parallel_time|bc -l)>>plot_data_points_${N}.dat
	done
	echo>>plot_data_points_${N}.dat
	echo>>plot_data_points_${N}.dat
    done
    gnuplot -e "name='plot_data_points_${N}.dat';name2='plot_data_points_${N}.png';name3='Speedup Chart for ${N} Points--Master Worker'" gnuplot3_4.sh
done

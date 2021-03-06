mpicc numerical_integration.c -o numerical_integration2
g++ numerical_integration_sequential.c -o  numerical_integration_sequential
a=1
b=500
N=1000000000
op=1000
sequential_time=0
for((N=10;N<=100000000;N=N*10));do
    echo>plot_Q2_points_${N}.dat
    for((op=10;op<=1000;op=op*100));do
        sequential_time=`./numerical_integration_sequential $a $b $N $op`
        for((process=2;process<=32;process=process*2));do
            parallel_time=`mpirun -n $process ./numerical_integration2 $a $b $N $op`
            echo $process $(echo $sequential_time/$parallel_time|bc -l)>>plot_Q2_points_${N}.dat
        done
        echo>>plot_Q2_points_${N}.dat
        echo>>plot_Q2_points_${N}.dat
    done
    gnuplot -e "name='plot_Q2_points_${N}.dat';name2='plot_Q2_points_${N}.png';name3='Speedup Chart for ${N} Points--Static'" gnuplot3_4.sh
done

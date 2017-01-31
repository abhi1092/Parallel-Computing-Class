#!/bin/bash
g++ parallel_num_int.c -fopenmp -o parallel_num_int

a=1
b=500
mode=1
n=100
operation_intensity=10
numthrds=1


for ((n=1000;n<=100000000;n=n*10));do
	for((Operation_Intensity=10;Operation_Intensity<=1000;Operation_Intensity=Operation_Intensity*100));do
			#echo >./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat
			mode=1
			sequential_time=`./parallel_num_int $numthrds $mode $a $b $n $Operation_Intensity`
			echo > ./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat
			for ((mode=2;mode<=4;mode=mode+1));do		
				for ((numthrds=1;numthrds<=16;numthrds=numthrds*2));do
				paralle_time=`./parallel_num_int $numthrds $mode $a $b $n $Operation_Intensity`
				echo  $numthrds $(echo "$sequential_time/$paralle_time"|bc -l)>>./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat
				done
				echo >>./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat
				echo >>./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat
				done
			gnuplot -e "name='./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.dat';name2='./paralle_int_num/points${n}Operation_Intensity${Operation_Intensity}.png';name3='No. of points ${n} & Operation Intensity ${Operation_Intensity}'" gnuplot.sh
		done
done


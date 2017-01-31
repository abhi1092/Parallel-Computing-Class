#!/bin/bash
g++ -O3 -march=native Assignment_3.cpp
g++ main.c -o main -lpthread
#Sequential time
#Parameters: a b N Operation Intensity.
a=1
b=500
k=0
for ((N=10;N<=100000000;N=N*10));do
	for ((Operation_Intensity=1;Operation_Intensity<=1000;Operation_Intensity=Operation_Intensity*10));do
		./a.out $a $b $N $Operation_Intensity>>./graphdata/data$k.dat
		k=$((k+1))
	done
done

k=0
for ((N=10;N<=100000000;N=N*10));do
	for ((Operation_Intensity=1;Operation_Intensity<=1000;Operation_Intensity=Operation_Intensity*10));do
		for ((granularity=10;granularity<=100000;granularity=granularity*100));do	
			for ((Num_thrds=2;Num_thrds<=16;Num_thrds=Num_thrds*2));do
				y=$(cat ./graphdata/data$k.dat)
				x=`./main $a $b $N $Operation_Intensity 1 $granularity $Num_thrds`
				echo $Num_thrds $(echo "$y/$x"|bc -l)>>./graphdata/plot$k.dat
			done	
			echo >>./graphdata/plot$k.dat
		done
		gnuplot -e "name='./graphdata/plot$k.dat';name2='./graphdata/plot$k.png'" gnuplot.sh
		k=$((k+1))

	done
done







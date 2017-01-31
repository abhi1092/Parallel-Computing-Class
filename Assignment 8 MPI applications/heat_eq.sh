mpicc heat_eq_2d.c -o heat_eq_2d 
g++ heat_eq_2d_seq.c -o heat_eq_2d_seq

#Strong Scaling
array_size[1]=15811
array_size[2]=50000
array_size[3]=111803 
echo >plot_heat.dat
for((i=1;i<4;i++));do
	sequential_time=`./heat_eq_2d_seq ${array_size[i]}`
	for((processor=2;processor<=32;processor++));do
		input_size=$((array_size[i]/processor*processor))
		parallel_time=`mpirun -n $processor ./heat_eq_2d $input_size`
		echo $processor $(echo $sequential_time/$parallel_time|bc -l)>>plot_heat.dat
	done
	echo>>plot_heat.dat
	echo>>plot_heat.dat
done
	gnuplot -e "name='plot_heat.dat';name2='plot_heat.png';name3='Speedup Chart-2D heat equation-Strong scaling'" gnuplot3_4.sh


#WeakScaling experiment
array_size[1]=15811
array_size[2]=31622
array_size[3]=63245 
echo >plot_heat_weak.dat
processor=2
input_size=$((array_size[1]/processor*processor))
time=`mpirun -n $processor ./heat_eq_2d $input_size`
echo $processor $time>>plot_heat_weak.dat

processor=4
input_size=$((array_size[2]/processor*processor))
time=`mpirun -n $processor ./heat_eq_2d $input_size`
echo $processor $time>>plot_heat_weak.dat

processor=8
input_size=$((array_size[3]/processor*processor))
time=`mpirun -n $processor ./heat_eq_2d $input_size`
echo $processor $time>>plot_heat_weak.dat

gnuplot -e "name='plot_heat_weak.dat';name2='plot_heat_weak.png';name3='Speedup Chart-2D heat equation-Weak scaling'" gnuplot3.sh


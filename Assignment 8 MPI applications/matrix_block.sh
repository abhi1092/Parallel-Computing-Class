mpicc matrix_block.c -o matrix_block 
g++ matrix_seq.c -o matrix_seq

#Strong Scaling
array_size[1]=15811
array_size[2]=70710
array_size[3]=141421 
echo >plot_matrix_block.dat
for((i=1;i<4;i++));do
	sequential_time=`./matrix_seq ${array_size[i]}`
	for((processor=2;processor<=32;processor++));do
		input_size=$((array_size[i]/processor*processor))
		parallel_time=`mpirun -n $processor ./matrix_block $input_size`
		echo $processor $(echo $sequential_time/$parallel_time|bc -l)>>plot_matrix_block.dat
	done
	echo>>plot_matrix_block.dat
	echo>>plot_matrix_block.dat
done
	gnuplot -e "name='plot_matrix_block.dat';name2='plot_matrix_hor.png';name3='Speedup Chart For Matrix Vertical Decomposition Strong Scaling'" gnuplot3_4.sh

#WeakScaling experiment
array_size[1]=22360
array_size[2]=38729
array_size[3]=63245 
echo >plot_matrix_block_weak.dat
processor=4
input_size=$((array_size[1]/processor*processor))
time=`mpirun -n $processor ./matrix_block $input_size`
echo $processor $time>>plot_matrix_block_weak.dat

processor=9
input_size=$((array_size[2]/processor*processor))
time=`mpirun -n $processor ./matrix_block $input_size`
echo $processor $time>>plot_matrix_block_weak.dat

processor=16
input_size=$((array_size[3]/processor*processor))
time=`mpirun -n $processor ./matrix_block $input_size`
echo $processor $time>>plot_matrix_block_weak.dat

gnuplot -e "name='plot_matrix_block_weak.dat';name2='plot_matrix_block.png';name3='Speedup Chart-Matrix Block Decomposition-Weak scaling'" gnuplot3.sh


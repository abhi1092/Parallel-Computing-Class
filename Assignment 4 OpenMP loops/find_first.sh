g++ find_first_theta_n.c -fopenmp -o find_first_theta_n
g++ find_first_theta_position.c -fopenmp -o find_first_theta_position
thread_num=0
array_size=1000000000
#mode 2 is sequential while mode 1 is parallel
sequential_time=`./find_first_theta_n $array_size $thread_num 2`
parallel_time=0
echo $sequential_time
echo >plot_data_find_first_n.dat
for ((thread_num=1;thread_num<=16;thread_num=thread_num*2));do
	parallel_time=`./find_first_theta_n $array_size $thread_num 1`
	echo $thread_num $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_data_find_first_n.dat
done
gnuplot -e "name='plot_data_find_first_n.dat';name2='plot_data_find_first_n.png';name3='Find First Theta n work'" gnuplot.sh

sequential_time=`./find_first_theta_position $array_size $thread_num 2`
parallel_time=0
echo $sequential_time
echo >plot_data_find_first_position.dat
for ((thread_num=1;thread_num<=16;thread_num=thread_num*2));do
	parallel_time=`./find_first_theta_position $array_size $thread_num 1`
	echo $thread_num $(echo "$sequential_time/$parallel_time"|bc -l)>>plot_data_find_first_position.dat
done

gnuplot -e "name='plot_data_find_first_position.dat';name2='plot_data_find_first_position.png';name3='Find First Theta Position work'" gnuplot2.sh

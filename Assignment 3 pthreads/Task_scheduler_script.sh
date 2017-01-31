#!/bin/bash
g++ straseen_mock.c -o straseen_mock
g++ task_schuler.c -lpthread -Wno-write-strings -o task_schuler
#Parameters Operation intensity
for ((i=1000;i<=100000000;i=i*10));do
	x=`./straseen_mock $i`
	y=`./task_schuler 2 $i`
	echo $i $(echo $x/$y|bc -l)>>./task_data/task_data.dat
done

gnuplot gnu_task_schdl.sh






#Linked List Execution Script
i=100
s=1000
t=0
m=10
g++ -O3 -march=native main.cpp
#Search Size 1000
./a.out 2 $s $i>data.dat
#Search Size 10000
s=$((s*m))
./a.out 2 $s $i>>data.dat
#Search Size 100000
s=$((s*m))
./a.out 2 $s $i>>data.dat
#Search Size 1000000
s=$((s*m))
./a.out 2 $s $i>>data.dat
#Search Size 10000000
s=$((s*m))
./a.out 2 $s $i>>data.dat
#Search Size 10000000
s=$((s*m))
./a.out 2 $s $i>>data.dat
#Search Size 100000000
s=$((s*m))
./a.out 2 $s $i>>data.dat


#Graph generated filename: graph.png
#ss2.sh Script for GNUPLOT
gnuplot ss2.sh

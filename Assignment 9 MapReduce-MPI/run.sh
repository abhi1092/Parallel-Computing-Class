mpicxx -O3 -I /home/abhishek/Downloads/mrmpi-7Apr14/src -c -o word_count.o word_count.cpp
mpicxx -o word_count word_count.o /home/abhishek/Downloads/mrmpi-7Apr14/src/libmrmpi_linux.a

mpirun -n 3 ./word_count test1.txt test2.txt test3.txt test4.txt

mpicxx -O3 -I /home/abhishek/Downloads/mrmpi-7Apr14/src -c -o word_sort.o word_sort.cpp
mpicxx -o word_sort word_sort.o /home/abhishek/Downloads/mrmpi-7Apr14/src/libmrmpi_linux.a

mpirun -n 3 ./word_sort test1.txt test2.txt test3.txt test4.txt

mpicxx -O3 -I /home/abhishek/Downloads/mrmpi-7Apr14/src -c -o word_hist.o word_hist.cpp
mpicxx -o word_hist word_hist.o /home/abhishek/Downloads/mrmpi-7Apr14/src/libmrmpi_linux.a

mpirun -n 3 ./word_hist test1.txt test2.txt test3.txt test4.txt

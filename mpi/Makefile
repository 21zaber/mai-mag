
lab1:
	g++ main.cpp -o main
	mpic++ lab01.cpp -o lab

lab2:
	g++ main2.cpp -o main
	mpic++ lab02.cpp -o lab

run4:
	mpirun -n 4 -q ./lab 
	md5sum output

run8:
	mpirun -n 8 -q ./lab
	md5sum output

run16:
	mpirun -n 16 -q ./lab
	md5sum output

run:
	./main
	md5sum output


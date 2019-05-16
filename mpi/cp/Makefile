
ARGS=256 256 10000 0.0001 test1

all: 
	mpic++ --std=c++11 main.cpp -o cp

run:
	mpirun -n 1 -q ./cp ${ARGS}
	md5sum output

run2:
	mpirun -n 2 -q ./cp ${ARGS}
	md5sum output

run4:
	mpirun -n 4 -q ./cp ${ARGS} 
	md5sum output

run8:
	mpirun -n 8 -q ./cp ${ARGS} 
	md5sum output

run16:
	mpirun -n 16 -q ./cp ${ARGS} 
	md5sum output


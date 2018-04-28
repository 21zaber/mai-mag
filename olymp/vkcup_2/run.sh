
g++ --std=c++11 dc.cpp -o zc
g++ --std=c++11 c3.cpp -o dc

for (( a = 0; a < 10000; a++ )) 
do
    python3 test.py > tmp
    ./zc < tmp > zc.out
    ./dc < tmp > dc.out
    cmp -s zc.out dc.out || echo fail && break;

done

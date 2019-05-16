#!/usr/bin/python3.5

import sys

if len(sys.argv) != 6:
    print('Usage ./gen.py <FILE> <X> <OFFSET> <LEN> <VALUE>.')
    exit(0)

with open(sys.argv[1], 'w') as f:
    x = int(sys.argv[2])
    offset = lambda x: eval(sys.argv[3])
    ln = lambda x: eval(sys.argv[4])
    value = lambda x: eval(sys.argv[5])

    for i in range(x):
        f.write('{} {} {}\n'.format(offset(i+1), ln(i+1), value(i+1)))





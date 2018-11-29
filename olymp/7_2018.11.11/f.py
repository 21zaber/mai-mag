t = int(input())
from math import sqrt

for i in range(t):
    a, b, c = map(int, input().split())

    if c < a+ b:
        print('NIE')
        continue

    if (c - a - b)**2 > 4 * a*b:
        print('TAK')
    else:
        print('NIE')

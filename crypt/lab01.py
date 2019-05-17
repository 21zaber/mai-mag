n = int(input())

import random

x = [random.randint(13, 99)]

def f(x):
    return x*x + 1

print('start seed', x[0])

for i in range(10000000):
    x.append(f(x[i]) % n)

    a = abs(x[-1] - x[-2])

    if n % a == 0:
        print('found', a, n / a, 'on {} iteration'.format(i))
        exit(0)




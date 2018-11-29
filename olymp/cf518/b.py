n = int(input())

from math import sqrt

s = int(sqrt(n)) + 2

d = {}

for i in range(2, s):
    if n % i == 0:
        d[i] = 0
        while n % i == 0:
            d[i] += 1
            n //= i


if n > 1:
    d[n] = 1


ans = 1
for k, v in d.items():
    ans *= v+1

print(ans)


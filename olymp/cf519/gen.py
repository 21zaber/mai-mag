n = int(input())

print(n)

a = 2 * 3 * 5 * 7 * 11
print(a // 2)
print(a // 3)
print(a // 5)
print(a // 7)

from random import randint

for i in range(n - 4):
    t = a // 11
    print(t)

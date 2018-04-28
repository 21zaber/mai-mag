import random

min_n = 10
max_n = 100
fr, to = 100, 1000

n = [random.randint(min_n, max_n) for i in range(3)]

s = set()
def urand():
    t = random.randint(fr, to)
    while t in s:
        t = random.randint(fr, to)

    s.add(t)
    return t

lst = []

for i in n:
    t = [urand() for i in range(i)]
    lst.append(t)


print(' '.join(list(map(str, n))))
for i in lst:
    print(' '.join(list(map(str, i)))) 

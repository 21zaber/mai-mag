from random import randint
 
n = randint(5, 10)
l = [randint(0, 1) for x in range(n)]
s = set()
 
count = 1

s = set()
print(n)
print(' '.join(list(map(str, l))))

for i in range(n, 0, -1):
    if i not in s:
        s.add(i)
        end = randint(1, n)
        while end == i:
            end = randint(1, n)
        s.add(end)
        print('{} {}'.format(i, end))

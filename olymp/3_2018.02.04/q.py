n = int(input())
e = int(input())

d = {}
for i in range(n):
    d[i+1] = set()

for i in range(e):
    l = set(list(map(int, input().split()))[1:])

    if 1 in l:
        for j in l:
            d[j].add(i)
    else:
        t = set()
        for j in l:
            t = t | d[j]

        for j in l:
            d[j] = t | d[j]


ln = len(d[1])

for i in range(n):
    if len(d[i+1]) == ln:
        print(i+1)


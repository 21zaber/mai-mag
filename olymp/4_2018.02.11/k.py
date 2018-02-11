n = int(input())

mask = list(map(int, input().split()))

v = []

for i in range(n-1):
    v.append(list(map(int, input().split())))

xr = n
for i in v:
    for j in i:
        xr = xr ^ j

if xr == 0:
    print(n)
    for i in v:
        print('{} {}'.format(*i))
    exit(0)

d = {}
l = []
for i in v:
    for j in i:
        l.append(j)
        if j not in d:
            d[j] = 0
        d[j] += 1

#print(d)

c = 0
cl = []

for i in range(1, n+1):
    if mask[i-1] == 1 and d[i] % 2 == 1:
        c+=1
        cl.append(i)

if c == 0:
    print(-1)
    exit(0)

if c == 1:
    to_change = cl[0] ^ xr
    if to_change in d or to_change == 0:
        print(-1)
        exit(0)
    
    trans = {cl[0]: to_change}
    print(n)
    def prnt(a, end='\n'):
        print(trans.get(a, a), end=end)
    for i in v:
        prnt(i[0], end=' ')
        prnt(i[1])
    exit(0)

tmp = 131072

print(n)
trans = {
    cl[0]: cl[0] ^ xr + tmp,
    cl[1]: cl[1] + tmp
}

def prnt(a, end='\n'):
    print(trans.get(a, a), end=end)
for i in v:
    prnt(i[0], end=' ')
    prnt(i[1])
exit(0)
        






n, k, m = map(int, input().split())

kmp = {i:i for i in range(n)}

u = {i:set() for i in range(n)}
v = []
for i in range(k):
    x, y = map(int, input().split())
    x += -1
    y += -1

    u[x].add(y)
    u[y].add(x)

for i in range(m):
    x, y = map(int, input().split())
    x += -1
    y += -1

    kx, ky = kmp[x], kmp[y]
    if ky not in u[kx] and kx not in u[ky]:
        # add v
        v.append(i+1)

        kmp[x] = ky
        u[ky].update(u[kx])


print(len(v))
print(' '.join(map(str, v)))


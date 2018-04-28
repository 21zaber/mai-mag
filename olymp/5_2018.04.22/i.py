pedges = []

bmoves = [(1,1), (1,2), (2,1), (1,0), (0, 1)]
moves = set()

for i in bmoves:
    moves.add(i)
    moves.add((-i[0], i[1]))
    moves.add((i[0], -i[1]))
    moves.add((-i[0], -i[1]))

m = [[i*3+j+1 for j in range(3)] for i in range(3)]

for i in range(3):
    for j in range(3):
        for mv in moves:
            x, y = i+mv[0], j+mv[1]
            if x >= 0 and y >= 0 and x < 3 and y < 3:
                pedges.append((m[i][j], m[x][y]))

edges = {}
for i in pedges:
    if i[0] not in edges:
        edges[i[0]] = set()
    edges[i[0]].add(i[1])

n = int(input())

path = []

for i in range(n):
    a, b = map(int, input().split())
    path.append((a,b))

v = []
vset = set()

if n > 1:
    if path[0][0] in path[1]:
        v.append(path[0][1])
    else:
        v.append(path[0][0])
    vset.add(v[-1])

    for i in path:
        if i[0] in vset:
            v.append(i[1])
        else:
            v.append(i[0])
        vset.add(v[-1])
else:
    v = [path[0][0], path[0][1]]
    vset = set(v)

excl = {v[0], v[-1]}

def dfs(l, r, ret=True):
    vset.add(l)
    ans = 1 
    if l in excl:
        ans = 0

    if ret:
        ans += dfs(r, l, ret=False)

    for i in edges[l]:
        if i not in vset:
            ans += dfs(i, r, ret=ret)
    if l not in excl:
        vset.discard(l)
#    print(l,r,ans)
    return ans

ans = dfs(v[0], v[-1])+1

print(ans*2)



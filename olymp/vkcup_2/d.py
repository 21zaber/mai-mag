n, a, b = map(int, input().split())

a -= 1
b -= 1

g = list(map(int, input().split()))
k = list(map(int, input().split()))

keys = {}
keys[k[a]] = [a, a]

way = [-1 for i in range(n)]
way[a] = 0
l, r = a, a

#print(keys)

for i in range(n):
    nl = l-1
    nr = r+1

    if nl >= 0:
        if g[nl] in keys:
            t = keys[g[nl]]

            if t[1] >= 0:
                fr = t[1]
            if t[0] >= 0:
                fr = t[0]

            way[nl] = way[fr] + abs(fr - nl)
            if k[nl] not in keys:
                keys[k[nl]] = [nl, -1]
            elif keys[k[nl]][0] < 0 or way[keys[k[nl]][0]] > way[nl]:
                keys[k[nl]][0] = nl
            l = nl
            continue
    if nr < n:
        if g[nr-1] in keys:
            t = keys[g[nr-1]]

            if t[0] >= 0:
                fr = t[0]
            if t[1] >= 0:
                fr = t[1]

            way[nr] = way[fr] + abs(fr - nr)
            if k[nr] not in keys:
                keys[k[nr]] = [-1, nr]
            elif keys[k[nr]][1] < 0 or way[keys[k[nr]][1]] > way[nr]:
                keys[k[nr]][1] = nr
            r = nr
            continue

    break

print(way[b])

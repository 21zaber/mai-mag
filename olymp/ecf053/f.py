n = int(input())

v = {}

for i in range(n-1):
    a,b = map(int,input().split())

    if a-1 not in v:
        v[a-1] = []
    if b-1 not in v:
        v[b-1] = []

    v[a-1].append(b-1)
    v[b-1].append(a-1)

#   if a-1 not in v:
#       v[a-1] = set()
#   if b-1 not in v:
#       v[b-1] = set()
#
#   v[a-1].add(b-1)
#   v[b-1].add(a-1)

l = [0 for i in range(n)]
fr = [-1 for i in range(n)]
used = [False for i in range(n)]

lst = []

def dfs(a):

    if used[a]:
        return

    used[a] = True
    lst.append(a)

    for i in v.get(a, []):
        if not used[i]:
            l[i] = l[a]+1
            fr[i] = a
            dfs(i)

#dfs(n // 2)
dfs(n//2)

print(lst)
print(l)
print(fr)

need = [len(v[i]) > 2 for i in range(n)]

p = -1
for i in range(n):
    if need[i] and (p < 0 or l[p] > l[i]):
        p = i

pair = [p]

p = -1
for i in range(n):
    if need[i] and (p < 0 or l[p] < l[i]):
        p = i

pair.append(p)
clen = abs(l[pair[0]] - l[pair[1]])

print(pair)
br = pair[0]

for i in range(1, n):
    c = lst[i]
    p = lst[i-1]

    if need[c]:
        if l[c] <= l[p]:
            print('change bridge', c, fr[c])
            br = fr[c]

        l1 = l[c] + l[pair[0]] - 2 * l[br]
        l2 = l[c] + l[pair[1]] - 2 * l[br]

        if clen < l1 or clen < l2:
            if l1 > l2:
                pair[1] = c
            else:
                pair[0] = c


print(pair)






n = int(input())

d = {}


for i in range(n):
    s,t = input().split()

    q = set(t)
    key = list(q)
    key.sort()
    key = ''.join(key)

    if not key in d:
        d[key] = []

    l = 0

    for j in range(len(s)-1, -1, -1):
        if s[j] in q:
            l += 1
        else:
            break

    if l:
        s = s[:-l]

    d[key].append((s, i))


ans = []

for _, m in d.items():
    dd = {}

    for i in m:
        if i[0] not in dd:
            dd[i[0]] = []
        dd[i[0]].append(i[1]+1)

    for _, v in dd.items():
        ans.append(v)

print(len(ans))
for i in ans:
    print(len(i), end=' ')
    print(' '.join(list(map(str, i))))
        


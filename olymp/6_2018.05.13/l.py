n = int(input())

d = {}
all_users = set()

for i in range(n):
    f, t = input().split()

    d[(f,t)] = -1 * d.get((f, t), -1)
    all_users.add(f)
    all_users.add(t)

u = {}

for f, t in d:
    if d[(f, t)] > 0:
        if t in u:
            u[t] += 1
        else:
            u[t] = 1

l = [(u[i], i) for i in u]
l.sort()
l = l[::-1]

if l:
    mx = l[0][0]
    ans = []
    for i in l:
        if i[0] == mx:
            ans = [i[1]] + ans
        else:
            break
    for i in ans:
        print(i)
else:
    l = list(all_users)
    l.sort()
    for i in l:
        print(i)

        

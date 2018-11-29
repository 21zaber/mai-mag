n, m = map(int, input().split())

ans = [[(i, i)] for i in range(n)]

k = n

for i in range(m):
    a, b = map(int, input().split())

    ans[a-1].append((a-1, k))
    ans[b-1].append((b-1, k))
    k += 1


for i in ans:
    print(len(i))
    for j in i:
        print(j[0]+1, j[1]+1)

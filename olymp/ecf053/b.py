n = int(input())

a = list(map(int, input().split()))
d = {}
for i in range(n):
    d[a[i]] = i+1

b = list(map(int, input().split()))

ans = []
c = 0

for i in b:
    if d[i] < c:
        ans.append(0)
    else:
        ans.append(d[i] - c)
        c = d[i]

    #print(d[i], c)

print(' '.join(list(map(str, ans))))



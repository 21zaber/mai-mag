n,m =map(int,input().split())

x = list(map(int, input().split()))
t = list(map(int, input().split()))

ans = [0 for i in range(m)]

tax = []
for i in range(n+m):
    if t[i] == 1:
        tax.append(x[i])

j = 0

for i in range(n+m):
    if t[i] == 0:
        while j < m-1 and abs(x[i]-tax[j]) > abs(x[i]-tax[j+1]):
            j += 1
        ans[j] += 1

print(' '.join(list(map(str, ans))))
exit(0)


i = 0
c = 0

while t[i] == 0:
    c += 1
    i += 1

ans[i] = c

lt = i
i += 1

while i < n+m:
    c = 0
    while i < n+m and t[i] == 0:
        c += 1
        i += 1

    if i < n + m:
        ans[lt] += c // 2 + c % 2
        ans[i] += c // 2
    else:
        ans[lt] += c

    lt = i
    i += 1


for i in range(n+m):
    if t[i] == 1:
        print(ans[i], end = ' ')

print()

n = int(input())

a = list(map(int, input().split()))

for i in range(n-1, 0, -1):
    a[i] -= a[i-1]


ans = []

for i in range(1, n):
    f = True

    for j in range(i, n):
        if a[j] != a[j-i]:
            f = False
            break

    if f:
        ans.append(i)

ans.append(n)

print(len(ans))
print(' '.join(list(map(str, ans))))


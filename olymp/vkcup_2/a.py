n, k = map(int, input().split())

m = list(map(int, input().split()))

ans = 1
pos = m[0]

for i in range(1, n):
    if m[i] - pos > k:
        print(-1)
        exit(0)

    if i == n - 1:
        break

    if m[i+1] - pos > k:
        ans += 1
        pos = m[i]

print(ans)

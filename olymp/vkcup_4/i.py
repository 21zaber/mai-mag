n = int(input())

m = []

for i in range(n):
    H, M = map(int, input().split(':'))
    m.append(H*60 + M)
    m.append(m[-1]+24*60)

m.sort()

ans = 0

for i in range(1, 2*n):
    if m[i] - m[i-1] > ans:
        ans = m[i] - m[i-1]

ans -= 1
print("{}:{}".format(ans // 60, ans % 60))


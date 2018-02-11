n = int(input())

c = 0

for i in range(1, n-1):
    a = i
    b = n - 2 - i
    c += a * b

ans = c * n
print(ans // 4)

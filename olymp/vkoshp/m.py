n, k = map(int, input().split())

a = list(map(int, input().split()))

c = 1
mc = 0

for i in range(1, n):
    if a[i] != a[i-1]:
        c += 1
    else:
        mc  = max(mc, c)
        c = 1


mc = max(mc, c)

print(mc)
    

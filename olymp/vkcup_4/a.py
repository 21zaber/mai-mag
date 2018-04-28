l,r  = map(int, input().split())

max_pow = 32

ans = 0
t = 1
for i in range(32):
    a = 1
    for j in range(32):
        x = t * a
        if x >=l and x <= r:
            ans += 1
        a *= 3
    t *= 2

print(ans)


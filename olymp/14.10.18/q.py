n,k,a = map(int,input().split())

mn = 10**10

for i in range(n):
    t, s = map(int, input().split())

    x = k // (t*a)
    y = x * (t+s)

    if k % (t*a) == 0:
        y -= s
    else:
        z = k - x*t*a
        y += z // a

        if z % a > 0:
            y += 1

    mn = min(y, mn)

print(mn)

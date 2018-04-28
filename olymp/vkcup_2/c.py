g, d, f = map(int, input().split())

gs = list(map(int, input().split()))
ds = list(map(int, input().split()))
fs = list(map(int, input().split()))

if g < 1 or d < 2 or f < 3:
    print(0)
    exit(0)

ans = 0

mn = min(g * d, g * f, d * (d-1) // 2, g * (g-1) // 2)

def rnd(a):
    if a > int(a):
        return int(a) + 1
    return int(a)

def check(a, b, c):
    if max(a, b) > 2 * min(a, b):
        return

    l = rnd(max(a / 2, b / 2))
    r = min(a * 2, b * 2)

    m = [gs, ds, fs]
    mult = 1
    for i in range(3):
        if c[i] == 0:
            continue


if g * d == mn:
    for i in gs:
        for j in ds:
            check(i, j, (0,1,3))
    print(ans)
    exit(0)

if g * d == mn:
    for i in gs:
        for j in ds:
            check(i, j, (0,1,3))
    print(ans)
    exit(0)

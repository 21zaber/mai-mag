x = 60 * int(input())

a, b = map(int, input().split())

x -= a
ca = x // a 
cb = x // b

if ca < cb:
    if x - ca * a >= b:
        ca += 1

    print(ca)
else:
    print(cb)



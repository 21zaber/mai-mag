

def gcd(a, b):
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)


p = int(input())
q = int(input())



if p == 0:
    print(p)
    exit(0)
elif q == 0:
    print(p-1)
    exit(0)

g = gcd(p,q)

if g == 1:
    print(0)
else:
    print(p - p // g)



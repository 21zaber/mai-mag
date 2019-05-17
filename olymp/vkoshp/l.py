t,n,a,b,k = map(int,input().split())

if n < k:
    print(0)
    exit(0)


a = min(a, t)
b = min(b, t)


bn = n // 2
an = n - bn

m = bn * b + an * a
m //= k

if (a < b):
    b, a = a, b
    bn, an = an, bn

if an < k:
    m2 = (b*bn)//(k-an)
    m = min(m, m2)

m = min(m, t)

print(m)


from math import sqrt

m =int(input())

for i in range(m):
    n, l = map(int, input().split())
    l*=1000

    lst = []

    for i in range(n):
        lst.append(list(map(int, input().split())))
        lst[-1][1] /=1000000

    lst.sort(key=lambda a: -a[1])

#    print(lst)

    v = 0
    s = 0
    t = 0

    for i in lst:
        a, tt = i
        ll = tt*(2*v + tt*a) /2
        if s + ll > l:
            t += (-2*v + sqrt(4*v*v - 2*(s-l)*a)) / a
            s = l
            break
        s += ll
        v += tt * a
        t += tt
        print(s, v, t)

    t += (l-s)/v

    print(t)

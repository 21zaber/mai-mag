a, c  = map(int, input().split())

from collections import defaultdict as DD

def smpl(a):
    d = DD(int)
    for i in range(2, a):
        while not a % i:
            d[i] += 1
            a //= i

    if a > 1:
        d[a] += 1

    return dict(d)

ad, cd = smpl(a), smpl(c)

print(ad, cd)

ans = 1

for k in cd:
    if cd[k] > ad.get(k, 0):
        ans *= k ** cd[k]

print(ans)

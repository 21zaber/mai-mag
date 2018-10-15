n, k = map(int, input().split())

l = list(map(int, input().split()))

mx = max(l)

# k max in a row

c = 0
mxc = 0
ans = 0
for j, i in enumerate(l):
    if i == mx:
        c += 1
        if c > mxc:
            mxc = c
            ans = j+1 - c
    else:
        c = 0

if mxc >= k:
    print(ans+1)
    exit(0)

if n == k:
    print(1)
    exit(0)

t = True
for i in range(1, k):
    if l[i] > l[i-1]:
        t = False
        break

if t and min(l[:k]) >= max(l[k:]):
    print(1)
    exit(0)

t = True
for i in range(n-2, n-k-1, -1):
    if l[i] > l[i+1]:
        t = False
        break

if t and min(l[-k:]) >= max(l[:-k]):
    print(n-k+1)
    exit(0)

print(-1)

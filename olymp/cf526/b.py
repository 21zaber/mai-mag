n, s = map(int, input().split())

v = list(map(int, input().split()))

if sum(v) < s:
    print(-1)
    exit(0)

mv = min(v)

for i in range(n):
    s -= v[i] - mv

if s < 1:
    print(mv)
    exit(0)

ans = mv - s // n
if s % n != 0:
    ans -= 1

print(ans)




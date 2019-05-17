c = input()

m, s = map(int, input().split())

t = int(input())

ans = 0

for i in range(t):
    q, w = input().split()
    w = int(w)

    if q == 'S':
        ans += min(s, w)
        s = max(0, s-w)

    if q == 'R':
        s = min(m, s+w)

print(c, s)



n, k = map(int, input().split())

s = input()
t = input()

q = 0

while s[q] == t[q]:
    q += 1

m = 1

for i in range(q, n):
    if s[i] == t[i]:
        continue

    m *= 2



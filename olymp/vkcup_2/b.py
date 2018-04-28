n, k = map(int, input().split())

m = []
empty = []
ans = 0

for i in range(n):
    s = input()

    for j in range(len(s)):
        if s[j] == '.':
            t = 0
            if j > 0:
                t += s[j-1] == 'S'
            if j < 11:
                t += s[j+1] == 'S'
            empty.append((t, i, j))
        if s[j] == 'S':
            if j > 0:
                ans += s[j-1] in ['P', 'S']
            if j < 11:
                ans += s[j+1] in ['P', 'S']

    m.append(list(s))

empty.sort(key=lambda x: x[0])


for i in range(k):
    t, x, y = empty[i]
    m[x][y] = 'x'
    ans += t

print(ans)

for i in m:
    print(''.join(i))


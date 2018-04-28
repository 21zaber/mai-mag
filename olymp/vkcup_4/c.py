n = int(input())
m = list(map(int, input().split()))

l = 1
for i in range(1, n):
    if m[i] == m[i-1]:
        l += 1
    else:
        break

f = False
frst = m[0]
for i in range(n):
    if i % l == 0:
        f = not f
    if (f and m[i] != frst) or (not f and m[i] == frst):
        print('NO')
        exit(0)

if n % l == 0:
    print('YES')
else:
    print('NO')



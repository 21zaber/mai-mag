n = int(input())

s = input()

p = None
for i in range(1, n):
    if s[i] != s[i-1]:
        p = i
        break

if p:
    print('YES')
    print(s[p-1:p+1])
else:
    print('NO')

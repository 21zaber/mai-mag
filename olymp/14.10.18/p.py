s = input()

k = int(input())

t = True


for i in range(len(s)):
    if s[i] != s[-i-1]:
        t = False
        break

if t:
    print('YES')
else:
    print('NO')

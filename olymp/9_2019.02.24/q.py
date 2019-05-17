n = int(input())

l = list(map(int, input().split()))

c = 1
a = []
for i in range(1, len(l)):
    if l[i] <= l[i-1]:
        c += 1
    else:
        a.append(c)
        c = 1

a.append(c)

ans = 1
mx = max(a)
#qq = [2**i for i in range(mx)]
#   for i in range(1, mx):
#       qq.append(qq[i-1] * 2)


for i in a:
    ans *= 2 ** (i-1)

print(ans)

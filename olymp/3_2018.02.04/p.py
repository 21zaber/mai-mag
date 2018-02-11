p = int(input())
q = int(input())

a = 0

ans = set()

ans.add(a)

for i in range(10000):
    a = (a+q) % p
    ans.add(a)
#    print(a)

print(p - len(ans))

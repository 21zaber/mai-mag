x = 60 * int(input())

a, b = map(int, input().split())

x -= a
c = x //max(a,b)

x -= c * max(a,b)

if x > b:
    c+=1

print(c)



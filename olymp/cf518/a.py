n,m,k,l = map(int, input().split())


if n-k < l:
    print(-1)
    exit(0)

a = k+l
b = a // m
if a%m:
    b += 1

if b * m > n:
    print(-1)
    exit(0)
    

print(b)




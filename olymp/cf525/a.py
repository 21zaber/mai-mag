x = int(input())

if x == 1:
    print(-1)
else:
    print(x, x)

exit(0)

a = x
b = 1
for i in range(2, x+1):
    if x % i == 0:
        b *= i
        break

if b == 1:
    print(-1)
    exit(0)

print(a, b)

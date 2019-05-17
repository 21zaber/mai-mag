
n = int(input())

x = 0

for a in range(n):
    for b in range(n):
        for c in range(n):
            if a == (b+c) % n or b == (a+c) %n or c == (a+b) % n:
                x += 1
                print(a,b,c, a+b, (a+b)%n)

        print()


print(x)


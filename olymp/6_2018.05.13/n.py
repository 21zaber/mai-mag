n = int(input())

if n < 4:
    print('No solution')
    exit(0)

END = ' '

if n % 2 == 1:
    x = n // 2 + 1
    for i in range(n//2+1):
        print((x + i * 2) % (n+1), end=END)
    x = 1 - x % 2
    if x == 0:
        x = 2
    for i in range(n//2):
        print(x + i * 2, end=END)
else:
    for i in range(n//2):
        print(n-i)
        print(i+1)

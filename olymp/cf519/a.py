n = int(input())

a = list(map(int, input().split()))

s = sum(a)

for k in range(max(a), 250):
    if n*k  > s * 2:
        print(k)
        exit(0)

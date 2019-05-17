n = int(input())

a = list(map(int,input().split()))

p = [1, 32/40, 1/2, 12/40]

m = 0
for i in range(len(a)):
    m += a[i] / n * p[i]


print(m)
